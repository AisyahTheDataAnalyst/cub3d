/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/11/16 16:37:24 by yosherau         ###   ########.fr       */
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

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}	t_keys;

typedef struct s_game
{
	t_parse		parse;
	t_player	player;
	t_map		map;
	t_raycast	raycast;
	t_keys		keys;
}	t_game;

void	all_cleanup(t_game *game);
void	parsing_cleanup(t_parse *parse, t_map *map);
int		raycasting(t_game *game);

#endif