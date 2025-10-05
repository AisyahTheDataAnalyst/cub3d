/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:32:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 21:05:50 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(char **av, t_parse *parse)
{
	if (is_it_cub_file(av[1]) == false)
	{
		ft_putendl_fd("Error\nNot a .cub type of file for the map", 2);
		return (1);
	}
	if (open_cub_file(av[1], parse) == false)
	{
		ft_putendl_fd("Error\nFailed to open map file", 2);
		return (1);
	}
	if (check_elements(parse) == 1)
	{
		ft_putstr_fd("Error\nElements is not properly structured: ", 2);
		ft_putendl_fd(parse->err_msg, 2);
		return (1);
	}
	if (check_map(parse) == 1)
	{
		ft_putstr_fd("Error\nMap is not properly structured: ", 2);
		ft_putendl_fd(parse->err_msg, 2);
		return (1);
	}
	return (0);
}

bool	is_it_cub_file(char *map_file)
{
	char	*file_type;

	file_type = ft_strrchr(map_file, '.');
	if (!file_type || ft_strncmp(file_type, ".cub", 5) != 0)
		return (false);
	return (true);
}

bool	open_cub_file(char *map_file, t_parse *parse)
{
	parse->map_fd = open(map_file, O_RDONLY);
	if (parse->map_fd == -1)
		return (false);
	return (true);
}

int	check_elements(t_parse *parse)
{
	char	*line;

	line = get_next_line(parse->map_fd);
	while (line)
	{
		if (ft_strncmp(line, "NO ", 4) == 0 && !parse->no_txt_flag)
			parse_north_texture(line, parse);
		else if (ft_strncmp(line, "SO ", 4) == 0 && !parse->so_txt_flag)
			parse_south_texture(line, parse);
		else if (ft_strncmp(line, "WE ", 4) == 0 && !parse->we_txt_flag)
			parse_west_texture(line, parse);
		else if (ft_strncmp(line, "EA ", 4) == 0 && !parse->ea_txt_flag)
			parse_east_texture(line, parse);
		else if ((ft_strncmp(line, "F ", 3) == 0 && !parse->floor_flag)
			|| ft_strncmp(line, "C ", 3) == 0 && !parse->ceiling_flag)
			parse_colour(line, parse);
		free(line);
		line = get_next_line(parse->map_fd);
	}
	if (parse->got_all_elements == 6)
		return (0);
	return (1);
}

int	check_map(t_parse *parse)
{
	char	*line;
	int		i;
	int		j;

	if (search_start_line_map(parse) < 0 || search_last_line_map(parse) < 0)
		return (parsing_err_msg(parse, INVALID_MAP), 1);
	parse->map_height = parse->last_line - parse->start_line + 1;
	if (parse->map_height < 3 || search_map_width(parse) < 3)
		return (parsing_err_msg(parse, INVALID_MAP), 1);
	parse->map = malloc(sizeof(char *) * (parse->map_height + 1));
	line = get_next_line(parse->map_fd);
	i = 0;
	while (line && i != parse->start_line)
	{
		free(line);
		i++;
		line = get_next_line(parse->map_fd);
	}
	line = save_map(parse, line, i);
	if (!is_map_valid(parse) == false || !map_fully_walled(parse) == false
		|| !is_map_last_in_file(line, parse, i) == false
		|| !is_valid_player(parse) == false)
		return (1);
	map_replace_space_with_zero(parse);
	return (0);
}
