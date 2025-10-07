/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:32:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 17:18:33 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	init_parsing(t_parse *parse, char **av);
static bool	got_all_elements(t_parse *parse);

int	parsing(t_parse *parse, char **av)
{
	init_parsing(parse, av);
	if (accurate_file_type(parse->map_filename, ".cub") == false)
	{
		ft_putendl_fd("Error\nNot a .cub type of file for the map", 2);
		return (1);
	}
	parse->map_fd = openable_file(parse->map_filename, parse->map_fd);
	if ( parse->map_fd == -1)
	{
		ft_putstr_fd("Error\nFailed to open file\n", 2);
		return (1);
	}
	if (!parse_elements(parse))
	{
		ft_putstr_fd("Error\nElements is not properly structured: ", 2);
		ft_putendl_fd(parse->err_msg, 2);
		return (1);
	}
	if (!parse_map(parse))
	{
		ft_putstr_fd("Error\nMap is not properly structured: ", 2);
		ft_putendl_fd(parse->err_msg, 2);
		return (1);
	}
	return (0);
}

static void	init_parsing(t_parse *parse, char **av)
{
	parse->map_filename = av[1];
	parse->height_start = INT_MAX;
	parse->height_end = -1;
	parse->width_start = INT_MAX;
	parse->width_end = -1;
	parse->map_fd = -1;
	parse->so_txt_fd = -1;
	parse->no_txt_fd = -1;
	parse->we_txt_fd = -1;
	parse->ea_txt_fd = -1;
}

int	parse_elements(t_parse *parse)
{
	char	*line;
	int 	i;

	line = get_next_line(parse->map_fd);
	while (line)
	{
		i = 0;
		while (line[i] && skip_whitespace(line[i]))
			i++;
		if (ft_strncmp(&line[i], "NO ", 3) == 0)
		{
			printf("no\n");
			parse_north_texture(&line[i], parse);
		}
		else if (ft_strncmp(&line[i], "SO ", 3) == 0)
		{
			printf("so\n");
			parse_south_texture(&line[i], parse);
		}
		else if (ft_strncmp(&line[i], "WE ", 3) == 0)
		{
			printf("we\n");
			parse_west_texture(&line[i], parse);
		}
		else if (ft_strncmp(&line[i], "EA ", 3) == 0)
		{
			printf("ea\n");
			parse_east_texture(&line[i], parse);
		}
		else if (ft_strncmp(&line[i], "F ", 2) == 0)
		{
			printf("f\n");
			parse_colour(&line[i], parse, FLOOR);
		}
		else if (ft_strncmp(&line[i], "C ", 2) == 0)
		{
			printf("c\n");
			parse_colour(&line[i], parse, CEILING);
		}
		free(line);
		line = get_next_line(parse->map_fd);
	}
	close(parse->map_fd);
	printf("%d\n", i);
	if (got_all_elements(parse))
		return (1);
	return (0);
}

static bool	got_all_elements(t_parse *parse)
{
	printf("notxt: %d\nsotxt: %d\nwetxt: %d\neatxt: %d\nf: %d\nc: %d\n", parse->no_txt_count, parse->so_txt_count, parse->we_txt_count, parse->ea_txt_count, parse->floor_count, parse->ceiling_count);
	if (parse->no_txt_count == 1 && parse->so_txt_count == 1
		&& parse->we_txt_count == 1 && parse->ea_txt_count == 1
		&& parse->floor_count == 1 && parse->ceiling_count == 1)
		{
			printf("got all elements!\n");
			return (true);
		}
	else if (parse->so_txt_count != 1)
		return (parse_err_msg(parse, INVALID_SO_COUNT), false);
	else if (parse->no_txt_count != 1)
		return (parse_err_msg(parse, INVALID_NO_COUNT), false);
	else if (parse->ea_txt_count != 1)
		return (parse_err_msg(parse, INVALID_EA_COUNT), false);
	else if (parse->we_txt_count != 1)
		return (parse_err_msg(parse, INVALID_WE_COUNT), false);
	else if (parse->floor_count != 1)
		return (parse_err_msg(parse, INVALID_FLOOR_COUNT), false);
	else if (parse->ceiling_count != 1)
		return (parse_err_msg(parse, INVALID_CEILING_COUNT), false);
	return (false);
}

int	parse_map(t_parse *parse)
{
	char	*line;

	parse->map_fd = openable_file(parse->map_filename, parse->map_fd);
	if (parse->map_fd == -1)
		return (parse_err_msg(parse, UNOPEN_MAP_FILE), 0);
	line = search_map_details(parse);
	if (!is_map_last_in_file(line, parse))
		return (parse_err_msg(parse, MAP_IS_NOT_LAST), 0);
	printf("height_s: %d height_e: %d\n", parse->height_start, parse->height_end);
	if ((parse->height_start < 7 && parse->height_start != INT_MAX)
		|| parse->height_end < 9)
		return (parse_err_msg(parse, INVALID_MAP), 0);
	printf("width_s: %d width_e: %d\n", parse->width_start, parse->width_end);
	parse->map_height = parse->height_end - parse->height_start + 1;
	parse->map_width = parse->width_end - parse->width_start + 1;
	printf("m_height: %d m_width: %d\n", parse->map_height, parse->map_width);
	if (parse->map_height < 3 || parse->map_width < 3)
		return (ft_putendl_fd("hereeeee", 2), parse_err_msg(parse, INVALID_MAP), 0);
	parse->map_fd = openable_file(parse->map_filename, parse->map_fd);
	if (parse->map_fd == -1)
		return (parse_err_msg(parse, UNOPEN_MAP_FILE), 0);
	save_map(parse);
	if (!is_map_valid(parse))
		return (0);
	map_replace_space_with_zero(parse);
	return (1);
}
