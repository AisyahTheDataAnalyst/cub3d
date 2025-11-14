/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:33:46 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/14 13:52:18 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "cub3d.h"

void	draw_ceil_floor(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		y = -1;
		while (++y < WINDOW_HEIGHT)
		{
			if (WINDOW_HEIGHT / 2 > y)
				my_mlx_pixel_put(&game->raycast.data, x, y,
					game->map.ceiling_colour);
			else
				my_mlx_pixel_put(&game->raycast.data, x, y,
					game->map.floor_colour);
		}
	}
}
