/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/13 13:20:36 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "raycasting.h"

typedef struct s_game
{
	t_parse		*parse;
	t_player	*player;
	t_map		*map;
	t_raycast	*raycast;
}				t_game;

void	all_cleanup(t_game *game);
void	parsing_cleanup(t_parse *parse, t_map *map);

#endif