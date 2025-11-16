/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:52:57 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/16 14:04:56 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "cub3d.h"

void	create_window(t_raycast *raycast)
{
	raycast->mlx_connection = mlx_init();
	raycast->mlx_window = mlx_new_window(raycast->mlx_connection,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
}

void	create_window_image(t_raycast *raycast)
{
	raycast->data.img = mlx_new_image(raycast->mlx_connection,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	raycast->data.addr = mlx_get_data_addr(raycast->data.img,
			&raycast->data.bpp, &raycast->data.ll, &raycast->data.endian);
}

void	clear_window(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			my_mlx_pixel_put(&game->raycast.data, x, y, 0x000000);
	}
}

int	destroy_window(t_game *game)
{
	all_cleanup(game);
	mlx_destroy_window(game->raycast.mlx_connection, game->raycast.mlx_window);
	mlx_destroy_display(game->raycast.mlx_connection);
	free(game->raycast.mlx_connection);
	exit(EXIT_SUCCESS);
}
