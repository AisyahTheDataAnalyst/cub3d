/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:26:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/12 19:13:33 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	all_cleanup(t_map *map)
{
	// raycasting_cleanup();
	parsing_cleanup(map->parse);
}

void	parsing_cleanup(t_parse *parse)
{
	if (parse->so_txt)
		free(parse->so_txt);
	if (parse->no_txt)
		free(parse->no_txt);
	if (parse->we_txt)
		free(parse->we_txt);
	if (parse->ea_txt)
		free(parse->ea_txt);
	if (parse->map)
		free_array(parse->map);
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
