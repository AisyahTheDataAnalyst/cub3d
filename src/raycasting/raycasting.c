/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:44:35 by yosherau          #+#    #+#             */
/*   Updated: 2025/10/24 23:15:20 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "raycasting.h"

void	raycasting(t_player *player, t_map *map, t_raycast *raycast)
{
	create_window(raycast);
	int	column = -1;
	while (++column < WINDOW_WIDTH)
	{
		double	cameraX = 2 * column / (double)WINDOW_WIDTH - 1;
		double	rayDirX = player->dir_x + player->plane_x * cameraX;
		double	rayDirY = player->dir_y + player->plane_y * cameraX;
		int	mapX = (int)player->x_pos;
		int	mapY = (int)player->y_pos;

		double	sideDistX;
		double	sideDistY;

		double	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		int	stepX;
		int	stepY;
		bool	wallHit = false;
		// int	side;
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->x_pos - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->x_pos) * deltaDistX;
		}
		if (rayDirY > 0)
		{
			stepY = -1;
			sideDistY = (player->y_pos - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->y_pos) * deltaDistY;
		}
		while (!wallHit)
		{
			printf("JERE\n");
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				// side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				// side = 1;
			}
			if(map->map[mapX][mapY] > 48)
			{
				wallHit = true;
				printf("%c\n", map->map[mapX][mapY]);
				printf("%d, %d\n", mapX, mapY);
			}
		}
	}
	printf("xit\n");
}
