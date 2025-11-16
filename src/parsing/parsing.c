/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:32:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/16 17:12:10 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	other_edge_cases_elements(char *str, t_parse *parse);
static bool	got_all_elements(t_parse *parse, char *line);

bool	parsing(t_parse *parse, t_player *player, t_map *map, char **av)
{
	char	*line;

	init_parsing(parse, av);
	if (!accurate_file_type(parse->map_filename, ".cub"))
		return (err_msg(parse, NOT_CUB_FILE), ft_putendl_fd("Error", 2),
			ft_putendl_fd(parse->err_msg, 2), false);
	parse->map_fd = open(parse->map_filename, O_RDONLY);
	if (parse->map_fd == -1)
		return (err_msg(parse, UNOPEN_MAP_FILE),
			ft_putendl_fd("Error", 2), ft_putendl_fd(parse->err_msg, 2), false);
	line = get_next_line(parse->map_fd);
	if (!parse_elements(parse, map, line))
		return (ft_putstr_fd("Error\nElements is not properly structured: ", 2),
			ft_putendl_fd(parse->err_msg, 2), false);
	if (!parse_map(parse, player, map))
		return (ft_putstr_fd("Error\nMap is not properly structured: ", 2),
			ft_putendl_fd(parse->err_msg, 2), false);
	if (!parse_player(player, map))
		return (ft_putendl_fd("Error\nView is not properly structured", 2),
			false);
	return (true);
}

bool	parse_elements(t_parse *parse, t_map *map, char *line)
{
	int		i;

	while (line && parse->elements_status)
	{
		i = 0;
		while (line[i] && skip_whitespace(line[i]))
			i++;
		if (!ft_strncmp(&line[i], "NO ", 3))
			parse->elements_status = parse_north_texture(&line[i], parse, map);
		else if (!ft_strncmp(&line[i], "SO ", 3))
			parse->elements_status = parse_south_texture(&line[i], parse, map);
		else if (!ft_strncmp(&line[i], "WE ", 3))
			parse->elements_status = parse_west_texture(&line[i], parse, map);
		else if (!ft_strncmp(&line[i], "EA ", 3))
			parse->elements_status = parse_east_texture(&line[i], parse, map);
		else if ((!ft_strncmp(&line[i], "F ", 2)
				|| !ft_strncmp(&line[i], "C ", 2)))
			parse->elements_status = parse_colour(&line[i], parse, map);
		else
			parse->elements_status = other_edge_cases_elements(&line[i], parse);
		free(line);
		line = get_next_line(parse->map_fd);
	}
	return (got_all_elements(parse, line));
}

static bool	other_edge_cases_elements(char *str, t_parse *parse)
{
	if (!str)
		return (true);
	parse->not_empty_map = true;
	if (only_chars_of_map_and_whitespace_in_whole_line(str) < 0)
	{
		parse->invalid_identifier = true;
		return (false);
	}
	if (only_chars_of_map_and_whitespace_in_whole_line(str) == 0)
		return (true);
	if (only_chars_of_map_and_whitespace_in_whole_line(str) == 1)
		return (true);
	return (false);
}

static bool	got_all_elements(t_parse *parse, char *line)
{
	if (line)
		free (line);
	close(parse->map_fd);
	if (!parse->not_empty_map)
		return (err_msg(parse, EMPTY_MAP), false);
	if (parse->invalid_identifier)
		return (err_msg(parse, INVALID_IDENTIFIER), false);
	if (parse->elements_status
		&& parse->no_txt_count == 1 && parse->so_txt_count == 1
		&& parse->we_txt_count == 1 && parse->ea_txt_count == 1
		&& parse->floor_count == 1 && parse->ceiling_count == 1)
		return (true);
	return (false);
}

bool	parse_map(t_parse *parse, t_player *player, t_map *map)
{
	char	*line;

	parse->map_fd = open(parse->map_filename, O_RDONLY);
	if (parse->map_fd == -1)
		return (err_msg(parse, UNOPEN_MAP_FILE), false);
	line = search_map_details(parse);
	if (!is_map_last_in_file(line, parse))
		return (err_msg(parse, MAP_IS_NOT_LAST), false);
	if ((parse->height_start < 7 || parse->height_start == INT_MAX)
		|| parse->height_end < 9)
		return (err_msg(parse, INVALID_MAP), false);
	parse->map_height = parse->height_end - parse->height_start + 1;
	parse->map_width = parse->width_end - parse->width_start + 1;
	if (parse->map_height < 3 || parse->map_width < 3)
		return (err_msg(parse, INVALID_MAP), false);
	if (!map_has_valid_chars_only(parse))
		return (false);
	parse->map_fd = open(parse->map_filename, O_RDONLY);
	if (parse->map_fd == -1)
		return (err_msg(parse, UNOPEN_MAP_FILE), false);
	save_map(parse, map);
	if (!is_map_valid(parse, player, map))
		return (false);
	return (true);
}
