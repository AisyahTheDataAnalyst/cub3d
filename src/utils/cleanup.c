/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:26:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/13 13:30:17 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_cleanup(t_game *game)
{
	// raycasting_cleanup();
	parsing_cleanup(game->parse, game->map);
}

void	parsing_cleanup(t_parse *parse, t_map *map)
{
	if (parse->so_txt)
		free(parse->so_txt);
	if (parse->no_txt)
		free(parse->no_txt);
	if (parse->we_txt)
		free(parse->we_txt);
	if (parse->ea_txt)
		free(parse->ea_txt);
	if (map->map)
		free_array(map->map);
	if (map->so_txt_fd > 3)
		close(map->so_txt_fd);
	if (map->no_txt_fd > 3)
		close(map->no_txt_fd);
	if (map->we_txt_fd > 3)
		close(map->we_txt_fd);
	if (map->ea_txt_fd > 3)
		close(map->ea_txt_fd);
	if (parse->map_fd > 3)
		close(parse->map_fd);
	get_next_line(-2);
}
