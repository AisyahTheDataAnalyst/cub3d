/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/14 13:46:47 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "raycasting.h"

# define ESC_KEY 65307
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define LEFT_KEY 65363
# define RIGHT_KEY 65361

typedef struct s_game
{
	t_parse		parse;
	t_player	player;
	t_map		map;
	t_raycast	raycast;
}	t_game;


void	all_cleanup(t_game *game);
void	parsing_cleanup(t_parse *parse, t_map *map);
int		raycasting(t_game *game);

#endif