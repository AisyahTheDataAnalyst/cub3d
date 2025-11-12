/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:44:35 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/02 15:04:55 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "cub3d.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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

	x = -1;
	for (int y = 0; y < WINDOW_HEIGHT; y++)
		for (int x = 0; x < WINDOW_WIDTH; x++)
			my_mlx_pixel_put(&game->raycast.data, x, y, 0x000000);
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
			drawEnd = WINDOW_HEIGHT;

		int	colour;
		if (side == 0)
			colour = 0x00E23434;
		else
			colour = 0x00C61D1D;
		for (int y = drawStart; y < drawEnd; y++)
			my_mlx_pixel_put(&game->raycast.data, x, y, colour);
	}
	// mlx_clear_window(game->raycast.mlx_connection, game->raycast.mlx_window);
	mlx_put_image_to_window(game->raycast.mlx_connection, game->raycast.mlx_window,
		game->raycast.data.img, 0, 0);
	return (EXIT_SUCCESS);
}
