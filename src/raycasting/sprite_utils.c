/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:25:34 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/16 16:43:29 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_sprites(void *mlx, char *wall_path, t_img_data *wall)
{
	int	width;
	int	height;

	wall->img = mlx_xpm_file_to_image(mlx, wall_path, &width, &height);
	wall->addr = mlx_get_data_addr(wall->img, &wall->bpp,
			&wall->ll, &wall->endian);
}

void	sprite_loader(t_game *game)
{
	int			index;
	char		*array[NUM_TEX];
	t_img_data	*walls[NUM_TEX];

	array[0] = game->map.no_txt;
	array[1] = game->map.we_txt;
	array[2] = game->map.so_txt;
	array[3] = game->map.ea_txt;
	walls[0] = &game->raycast.assets.n_wall;
	walls[1] = &game->raycast.assets.w_wall;
	walls[2] = &game->raycast.assets.s_wall;
	walls[3] = &game->raycast.assets.e_wall;
	index = -1;
	while (++index < NUM_TEX)
		load_sprites(game->raycast.mlx_connection, array[index], walls[index]);
}
