/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:32:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/12 19:51:30 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	other_edge_cases_elements(char *str, t_parse *parse);
static bool	got_all_elements(t_parse *parse, char *line);

int	parsing(t_parse *parse, char **av)
{
	char	*line;

	init_parsing(parse, av);
	if (!accurate_file_type(parse->map_filename, ".cub"))
		return (parse_err_msg(parse, NOT_CUB_FILE), ft_putendl_fd("Error", 2),
			ft_putendl_fd(parse->err_msg, 2), 1);
	parse->map_fd = openable_file(parse->map_filename, parse->map_fd);
	if (parse->map_fd == -1)
		return (parse_err_msg(parse, UNOPEN_MAP_FILE),
			ft_putendl_fd("Error", 2), ft_putendl_fd(parse->err_msg, 2), 1);
	line = get_next_line(parse->map_fd);
	if (!parse_elements(parse, line))
		return (ft_putstr_fd("Error\nElements is not properly structured: ", 2),
			ft_putendl_fd(parse->err_msg, 2), 1);
	if (!parse_map(parse))
		return (ft_putstr_fd("Error\nMap is not properly structured: ", 2),
			ft_putendl_fd(parse->err_msg, 2), 1);
	return (0);
}

int	parse_elements(t_parse *parse, char *line)
{
	int		i;

	while (line && parse->elements_status)
	{
		i = 0;
		while (line[i] && skip_whitespace(line[i]))
			i++;
		if (!ft_strncmp(&line[i], "NO", 2) && skip_whitespace(line[i + 2]))
			parse->elements_status = parse_north_texture(&line[i], parse);
		else if (!ft_strncmp(&line[i], "SO", 2) && skip_whitespace(line[i + 2]))
			parse->elements_status = parse_south_texture(&line[i], parse);
		else if (!ft_strncmp(&line[i], "WE", 2) && skip_whitespace(line[i + 2]))
			parse->elements_status = parse_west_texture(&line[i], parse);
		else if (!ft_strncmp(&line[i], "EA", 2) && skip_whitespace(line[i + 2]))
			parse->elements_status = parse_east_texture(&line[i], parse);
		else if ((!ft_strncmp(&line[i], "F", 1)
				|| !ft_strncmp(&line[i], "C", 1))
			&& skip_whitespace(line[i + 1]))
			parse->elements_status = parse_colour(&line[i], parse);
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

	// printf("notxt: %d\nsotxt: %d\nwetxt: %d\neatxt: %d\nf: %d\nc: %d\n",
	// parse->no_txt_count, parse->so_txt_count, parse->we_txt_count,
	// parse->ea_txt_count, parse->floor_count, parse->ceiling_count);
		// printf("got all elements!\n");
static bool	got_all_elements(t_parse *parse, char *line)
{
	if (line)
		free (line);
	close(parse->map_fd);
	if (!parse->not_empty_map)
		return (parse_err_msg(parse, EMPTY_MAP), false);
	if (parse->invalid_identifier)
		return (parse_err_msg(parse, INVALID_IDENTIFIER), false);
	if (parse->elements_status
		&& parse->no_txt_count == 1 && parse->so_txt_count == 1
		&& parse->we_txt_count == 1 && parse->ea_txt_count == 1
		&& parse->floor_count == 1 && parse->ceiling_count == 1)
		return (true);
	if (parse->no_txt_count != 1)
		return (parse_err_msg(parse, INVALID_NO_COUNT), false);
	if (parse->so_txt_count != 1)
		return (parse_err_msg(parse, INVALID_SO_COUNT), false);
	if (parse->we_txt_count != 1)
		return (parse_err_msg(parse, INVALID_WE_COUNT), false);
	if (parse->ea_txt_count != 1)
		return (parse_err_msg(parse, INVALID_EA_COUNT), false);
	if (parse->floor_count != 1)
		return (parse_err_msg(parse, INVALID_FLOOR_COUNT), false);
	if (parse->ceiling_count != 1)
		return (parse_err_msg(parse, INVALID_CEILING_COUNT), false);
	return (true);
}

	// printf("height_s: %d height_e: %d\n", 
	// parse->height_start, parse->height_end);
	// printf("width_s: %d width_e: %d\n", 
	// parse->width_start, parse->width_end);
	// printf("m_height: %d m_width: %d\n", 
	// parse->map_height, parse->map_width);
int	parse_map(t_parse *parse)
{
	char	*line;

	parse->map_fd = openable_file(parse->map_filename, parse->map_fd);
	if (parse->map_fd == -1)
		return (parse_err_msg(parse, UNOPEN_MAP_FILE), 0);
	line = search_map_details(parse);
	if (!is_map_last_in_file(line, parse))
		return (parse_err_msg(parse, MAP_IS_NOT_LAST), 0);
	if ((parse->height_start < 7 && parse->height_start != INT_MAX)
		|| parse->height_end < 9)
		return (parse_err_msg(parse, INVALID_MAP), 0);
	parse->map_height = parse->height_end - parse->height_start + 1;
	parse->map_width = parse->width_end - parse->width_start + 1;
	if (parse->map_height < 3 || parse->map_width < 3)
		return (parse_err_msg(parse, INVALID_MAP), 0);
	if (!map_has_valid_chars_only(parse))
		return (0);
	parse->map_fd = openable_file(parse->map_filename, parse->map_fd);
	if (parse->map_fd == -1)
		return (parse_err_msg(parse, UNOPEN_MAP_FILE), 0);
	save_map(parse);
	if (!is_map_valid(parse))
		return (0);
	map_replace_space_with_wall(parse);
	return (1);
}
