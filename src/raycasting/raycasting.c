/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:44:35 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/14 17:17:35 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	get_pixel_color(t_img_data *data, int x, int y)
{
	char	*pixel;
	x = 64 - x;
	if (x < 0)
		x = 0;
	if (x >= 64)
		x = 64;
	if (y < 0)
		y = 0;
	if (y >= 64)
		y = 64;
	pixel = data->addr + (y * data->ll + x * (data->bpp / 8));
	return (*(unsigned int *)pixel);
}

double	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 1000000);
}

void	init_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player.x_pos - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->player.x_pos)
			* ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.y_pos - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->player.y_pos)
			* ray->deltaDistY;
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->rayDirX = ray->cameraX * game->player.plane_x + game->player.dir_x;
	ray->rayDirY = ray->cameraX * game->player.plane_y + game->player.dir_y;
	ray->mapX = (int)game->player.x_pos;
	ray->mapY = (int)game->player.y_pos;
	ray->hit = 0;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	init_step_and_side(game, ray);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->map.map[ray->mapY][ray->mapX] == 49)
			ray->hit = 1;
	}
}

void	calculate_wall(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	ray->lineHeight = (int)(WINDOW_HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (ray->drawEnd > WINDOW_HEIGHT)
		ray->drawEnd = WINDOW_HEIGHT - 1;
	if (ray->side == 0)
		ray->wallX = game->player.y_pos + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = game->player.x_pos + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor((ray->wallX));
	ray->texX = (int)(ray->wallX * (double)64);
	if (ray->side == 0 && ray->rayDirX > 0)
		ray->texX = 64 - ray->texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		ray->texX = 64 - ray->texX - 1;
}

void	draw_walls(t_game *game, t_ray *ray, int x)
{
	int	y;

	ray->step = 1.0 * 64 / ray->lineHeight;
	ray->texPos = (ray->drawStart - WINDOW_HEIGHT / 2 + ray->lineHeight / 2)
		* ray->step;
	y = ray->drawStart;
	while (++y < ray->drawEnd)
	{
		ray->texY = (int)ray->texPos & (64 - 1);
		ray->texPos += ray->step;
		if (ray->side == 1 && ray->rayDirY < 0)
			ray->color = get_pixel_color(&game->raycast.assets.n_wall, ray->texX, ray->texY);
		else if (ray->side == 1 && ray->rayDirY > 0)
			ray->color = get_pixel_color(&game->raycast.assets.s_wall, ray->texX, ray->texY);
		if (ray->side == 0 && ray->rayDirX > 0)
			ray->color = get_pixel_color(&game->raycast.assets.e_wall, ray->texX, ray->texY);
		if (ray->side == 0 && ray->rayDirY < 0)
			ray->color = get_pixel_color(&game->raycast.assets.w_wall, ray->texX, ray->texY);
		my_mlx_pixel_put(&game->raycast.data, x, y, ray->color);
	}
}

int	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	clear_window(game);
	draw_ceil_floor(game);
	while (++x < WINDOW_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall(game, &ray);
		draw_walls(game, &ray, x);
	}
	mlx_put_image_to_window(game->raycast.mlx_connection,
		game->raycast.mlx_window, game->raycast.data.img, 0, 0);
	return (EXIT_SUCCESS);
}
