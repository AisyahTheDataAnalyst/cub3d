/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:26:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/16 12:42:29 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_resources(t_game *game)
{
	mlx_destroy_image(game->raycast.mlx_connection, game->raycast.data.img);
	mlx_destroy_image(game->raycast.mlx_connection,
		game->raycast.assets.n_wall.img);
	mlx_destroy_image(game->raycast.mlx_connection,
		game->raycast.assets.s_wall.img);
	mlx_destroy_image(game->raycast.mlx_connection,
		game->raycast.assets.e_wall.img);
	mlx_destroy_image(game->raycast.mlx_connection,
		game->raycast.assets.w_wall.img);
}

void	all_cleanup(t_game *game)
{
	parsing_cleanup(&game->parse, &game->map);
}
	// free_resources(game);

void	parsing_cleanup(t_parse *parse, t_map *map)
{
	if (map->so_txt)
		free(map->so_txt);
	if (map->no_txt)
		free(map->no_txt);
	if (map->we_txt)
		free(map->we_txt);
	if (map->ea_txt)
		free(map->ea_txt);
	if (map->map)
		free_array(map->map);
	if (parse->so_txt_fd > 3)
		close(parse->so_txt_fd);
	if (parse->no_txt_fd > 3)
		close(parse->no_txt_fd);
	if (parse->we_txt_fd > 3)
		close(parse->we_txt_fd);
	if (parse->ea_txt_fd > 3)
		close(parse->ea_txt_fd);
	if (parse->map_fd > 3)
		close(parse->map_fd);
	get_next_line(-2);
}
