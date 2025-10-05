/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:27:28 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 21:05:25 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdbool.h> //bool
# include <fcntl.h> // open
# include <limits.h> // INT_MIN, INT_MAX

// err_msg
# define MAP_IS_NOT_LAST "Map is not at the last position in file"
# define MANY_NO "Exist more than 1 path for north texture"
# define MANY_SO "Exist more than 1 path for south texture"
# define MANY_EA "Exist more than 1 path for east texture"
# define MANY_WE "Exist more than 1 path for west texture"
# define INVALID_NO "Invalid path to north texture"
# define INVALID_SO "Invalid path to south texture"
# define INVALID_EA "Invalid path to east texture"
# define INVALID_WE "Invalid path to west texture"
# define MANY_PLAYERS "Players exist more than 1"
# define INVALID_COLOUR "Invalid colour"
# define NOT_XPM_FILE "Not a .xpm type of file for texture"
# define INVALID_MAP "Map is invalid"
# define FLOOR 0
# define CEILING 1

typedef struct s_parse
{
	int		got_all_elements;
	char	**map;				//malloc
	char	*no_txt;			//malloc
	char	*so_txt;			//malloc
	char	*ea_txt;			//malloc
	char	*we_txt;			//malloc
	int		floor_colour;		
	int		ceiling_colour;
	char	player_direction;
	int		player_row;
	int		player_col;
	bool	no_txt_flag;
	bool	so_txt_flag;
	bool	we_txt_flag;
	bool	ea_txt_flag;	
	bool	floor_flag;
	bool	ceiling_flag;
	int		player_count;
	int		map_height;
	int		start_line;
	int		last_line;
	int		map_width;
	int		width_start;
	int		width_end;
	int		map_fd;
	char	*err_msg;
}	t_parse;


#endif
