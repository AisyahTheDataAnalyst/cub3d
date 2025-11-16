/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:47:15 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/16 16:40:43 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_img_data *data, int x, int y)
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

void	update_player(t_game *game)
{
	const double	rot_speed = 0.02;

	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		move_left(game);
	if (game->keys.d)
		move_right(game);
	if (game->keys.left)
		rotate(game, rot_speed);
	if (game->keys.right)
		rotate(game, -rot_speed);
}

void	fill_ceil_floor(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		y = -1;
		while (++y < WINDOW_HEIGHT)
		{
			if (y < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(&game->raycast.data, x, y,
					game->map.ceiling_colour);
			else
				my_mlx_pixel_put(&game->raycast.data, x, y,
					game->map.floor_colour);
		}
	}
}
