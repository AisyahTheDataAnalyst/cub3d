/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:27:28 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/16 09:57:09 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "map_player.h"
# include <stdbool.h> //bool
# include <fcntl.h> // open
# include <limits.h> // INT_MIN, INT_MAX
# include <stdio.h> // printf

// err_msg
# define MAP_IS_NOT_LAST "Map is not at the last position in file"
# define INVALID_NO_COUNT "Invalid number of north element"
# define INVALID_SO_COUNT "Invalid number of south element"
# define INVALID_EA_COUNT "Invalid number of east element"
# define INVALID_WE_COUNT "Invalid number of west element"
# define INVALID_FLOOR_COUNT "Invalid number of floor element"
# define INVALID_CEILING_COUNT "Invalid number of ceiling element"
# define INVALID_PLAYER "Invalid number of player"
# define INVALID_COLOUR "Invalid colour"
# define NOT_XPM_FILE_NO "Not a .xpm type of file for north texture"
# define NOT_XPM_FILE_SO "Not a .xpm type of file for south texture"
# define NOT_XPM_FILE_EA "Not a .xpm type of file for east texture"
# define NOT_XPM_FILE_WE "Not a .xpm type of file for west texture"
# define NOT_CUB_FILE "Not a .cub type of file for map"
# define INVALID_MAP "Map is invalid"
# define UNOPEN_MAP_FILE "Failed to open map file"
# define UNOPEN_TXT_FILE "Failed to open texture file"
# define INVALID_IDENTIFIER "Map file exists invalid identifier"
# define EMPTY_MAP "Map file is empty"
# define INVALID_WHITESPACE "Not spaces only between info and element or no info"

# define FLOOR 0
# define CEILING 1

typedef struct s_parse
{
	int		so_txt_fd;
	int		no_txt_fd;
	int		we_txt_fd;
	int		ea_txt_fd;
	int		map_height;
	int		map_width;
	bool	elements_status;
	bool	invalid_identifier;
	bool	not_empty_map;
	int		no_txt_count;
	int		so_txt_count;
	int		we_txt_count;
	int		ea_txt_count;	
	int		floor_count;
	int		ceiling_count;
	int		*rgb;
	int		colour_mode;
	int		player_count;
	int		height_start;
	int		height_end;
	int		width_start;
	int		width_end;
	int		map_fd;
	char	*map_filename;
	char	*err_msg;
}	t_parse;

// parsing.c
int		parsing(t_parse *parse, t_player *player, t_map *map, char **av);
int		parse_elements(t_parse *parse, t_map *map, char *line);
int		parse_map(t_parse *parse, t_player *player, t_map *map);

// textures.c
bool	parse_north_texture(char *str, t_parse *parse, t_map *map);
bool	parse_south_texture(char *str, t_parse *parse, t_map *map);
bool	parse_west_texture(char *str, t_parse *parse, t_map *map);
bool	parse_east_texture(char *str, t_parse *parse, t_map *map);

// colours.c
bool	parse_colour(char *str, t_parse *parse, t_map *map);

// search_map_details.c
char	*search_map_details(t_parse *parse);

// map_1.c
bool	is_map_last_in_file(char *line, t_parse *parse);
bool	map_has_valid_chars_only(t_parse *parse);
void	save_map(t_parse *parse, t_map *map);

// map_2.c
bool	is_map_valid(t_parse *parse, t_player *player, t_map *map);
void	map_replace_space_with_wall(t_map *map);
// void	print_map(char **map)
// void	print_dup_map(char **dup_map)

// player.c
bool	parse_player(t_player *player, t_map *map);
bool	is_player_valid(t_parse *parse, t_player *player, t_map *map);

// utils_char.c
bool	is_char_of_map(char c);
int		only_chars_of_map_and_whitespace_in_whole_line(char *line);
int		only_chars_of_map_in_whole_line(char *line);
bool	skip_whitespace(char c);
int		char_repitition(char *str, char c);

// utils.c
void	init_parsing(t_parse *parse, char **av);
void	err_msg(t_parse *parse, char *msg);
void	free_array(char **str);
bool	accurate_file_type(char *map_filename, char *file_extension);
bool	is_space(char c);

#endif