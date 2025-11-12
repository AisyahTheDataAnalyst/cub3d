/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:44:35 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/12 14:24:21 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
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
	pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec * 1000000);
}

int	raycasting(t_game *game)
{
	int	x;
	
	// mlx_clear_window(game->raycast.mlx_connection, game->raycast.mlx_window);
	x = -1;
	for (int y = 0; y < WINDOW_HEIGHT; y++)
		for (int x = 0; x < WINDOW_WIDTH; x++)
			my_mlx_pixel_put(&game->raycast.data, x, y, 0x000000);

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		int y = -1;
		while (++y < WINDOW_HEIGHT)
		{
			if (WINDOW_HEIGHT / 2  > y)
				my_mlx_pixel_put(&game->raycast.data, x, y, game->map.ceiling_colour);
			else
				my_mlx_pixel_put(&game->raycast.data, x, y, game->map.floor_colour);
		}
	}
	
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		double	cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		double	rayDirX = cameraX * game->player.plane_x + game->player.dir_x;
		double	rayDirY = cameraX * game->player.plane_y + game->player.dir_y;

		int	mapX = (int)game->player.x_pos;
		int	mapY = (int)game->player.y_pos;

		double	sideDistX;
		double	sideDistY;

		double	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double	perpWallDist;

		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.x_pos - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.x_pos) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.y_pos - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.y_pos) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map.map[mapY][mapX] == 49)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int	lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

		int	drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
		if (drawEnd > WINDOW_HEIGHT)
			drawEnd = WINDOW_HEIGHT - 1;

		double	wallX;
		if (side == 0)
			wallX = game->player.y_pos + perpWallDist * rayDirY;
		else
			wallX = game->player.x_pos + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int	texX = (int)(wallX * (double)64);
		if (side == 0 && rayDirX > 0)
			texX = 64 - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = 64 - texX - 1;
		
		double	step = 1.0 * 64 / lineHeight;
		double	texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
		int		color;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int	texY = (int)texPos & (64 - 1);
			texPos += step;
			if (side == 1 && rayDirY < 0)
				color = get_pixel_color(&game->raycast.assets.n_wall, texX, texY);
			else if (side == 1 && rayDirY > 0)
				color = get_pixel_color(&game->raycast.assets.s_wall, texX, texY);
			else if (side == 0 && rayDirX > 0)
				color = get_pixel_color(&game->raycast.assets.e_wall, texX, texY);
			else if (side == 0 && rayDirX < 0)
				color = get_pixel_color(&game->raycast.assets.w_wall, texX, texY);
			my_mlx_pixel_put(&game->raycast.data, x, y, color);
		}
	}
	
	mlx_put_image_to_window(game->raycast.mlx_connection, game->raycast.mlx_window,
		game->raycast.data.img, 0, 0);
	return (EXIT_SUCCESS);
}
