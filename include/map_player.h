/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:29:12 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/15 21:01:56 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PLAYER_H
# define MAP_PLAYER_H

typedef struct s_player
{
	char	player_direction;
	double	y_pos;
	double	x_pos;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct s_map
{
	char	**map;				//malloc
	char	*no_txt;			//malloc
	char	*so_txt;			//malloc
	char	*we_txt;			//malloc
	char	*ea_txt;			//malloc
	int		floor_colour;
	int		ceiling_colour;
}				t_map;

#endif