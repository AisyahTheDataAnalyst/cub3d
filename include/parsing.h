/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:27:28 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 17:48:34 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdbool.h> //bool
# include <fcntl.h> // open
# include <limits.h> // INT_MIN, INT_MAX

# include <stdio.h>

// err_msg
# define MAP_IS_NOT_LAST "Map is not at the last position in file"
# define INVALID_NO_COUNT "Invalid number of north element"
# define INVALID_SO_COUNT "Invalid number of south element"
# define INVALID_EA_COUNT "Invalid number of east element"
# define INVALID_WE_COUNT "Invalid number of west element"
# define INVALID_FLOOR_COUNT "Invalid number of floor element"
# define INVALID_CEILING_COUNT "Invalid number of ceiling element"
// # define INVALID_NO "Invalid path to north texture"
// # define INVALID_SO "Invalid path to south texture"
// # define INVALID_EA "Invalid path to east texture"
// # define INVALID_WE "Invalid path to west texture"
# define INVALID_PLAYER "Invalid number of player"
# define INVALID_COLOUR "Invalid colour"
# define NOT_XPM_FILE "Not a .xpm type of file for texture"
# define INVALID_MAP "Map is invalid"
# define UNOPEN_MAP_FILE "Failed to open map file"
# define UNOPEN_TXT_FILE "Failed to open texture file"
# define FLOOR 0
# define CEILING 1

typedef struct s_parse
{
	char	**map;				//malloc
	char	*no_txt;			//malloc
	char	*so_txt;			//malloc
	char	*ea_txt;			//malloc
	char	*we_txt;			//malloc
	int		floor_colour;		
	int		ceiling_colour;
	char	player_direction;
	int		map_height;
	int		map_width;
	int		player_y_pos;
	int		player_x_pos;
	bool	got_all_elements;
	int		no_txt_count;
	int		so_txt_count;
	int		we_txt_count;
	int		ea_txt_count;	
	int		floor_count;
	int		ceiling_count;
	int		player_count;
	int		height_start;
	int		height_end;
	int		width_start;
	int		width_end;
	int		map_fd;
	int		so_txt_fd;
	int		no_txt_fd;
	int		we_txt_fd;
	int		ea_txt_fd;
	char	*map_filename;
	char	*err_msg;			//malloc
}	t_parse;


// parsing.c
int		parsing(t_parse *parse, char **av);
int		parse_elements(t_parse *parse);
int		parse_map(t_parse *parse);

// textures.c
void	parse_north_texture(char *str, t_parse *parse);
void	parse_south_texture(char *str, t_parse *parse);
void	parse_west_texture(char *str, t_parse *parse);
void	parse_east_texture(char *str, t_parse *parse);

// colours.c
void	parse_colour(char *str, t_parse *parse, int colour_mode);

// search_map_details.c
char	*search_map_details(t_parse *parse);

// map.c
bool	is_map_last_in_file(char *line, t_parse *parse);
void	save_map(t_parse *parse);
bool	is_map_valid(t_parse *parse);
void	map_replace_space_with_zero(t_parse *parse);

// player.c
bool	is_player_valid(t_parse *parse);

// utils_char.c
bool	is_char_of_map(char c);
bool	only_chars_of_map_in_whole_line(char *line);
bool	skip_whitespace(char c);
int		char_repitition(char *str, char c);

// utils.c
void	parse_err_msg(t_parse *parse, char *msg);
void	free_array(char **str);
bool	accurate_file_type(char *map_filename, char *file_extension);
int		openable_file(char *map_filename, int fd);
void	parsing_cleanup(t_parse *parse);




#endif
