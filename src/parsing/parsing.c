/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:32:41 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/02 19:42:13 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing(char **av, t_parse *parse)
{
	if (is_it_cub_file(av[1]) == false)
		return (ft_putendl_fd("Error\nNot a .cub type of file for the map", 2), 1);
	if (open_cub_file(av[1], parse) == false)
		return (ft_putendl_fd("Error\nUnable to open map file", 2), 1);
	if (parse_elements(parse) == 1)
		return (ft_putendl_fd("Error\nElements is not properly structured", 2), 1);
	if (check_map(parse) == 1)
		return (ft_putendl_fd("Error\nMap is not properly structured", 2), 1);
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

int	parse_elements(t_parse *parse)
{
	char	*line;
	char	*clean_line;

	line = get_next_line(parse->map_fd);
	while (line)
	{
		clean_line = ft_strtrim(line, " \t\n");
		free(line);
		if (ft_strncmp(clean_line, "NO ", 4) == 0)
			parse_north_texture(clean_line, parse);
		else if (ft_strncmp(clean_line, "SO ", 4) == 0)
			parse_south_texture(clean_line, parse);
		else if (ft_strncmp(clean_line, "WE ", 4) == 0)
			parse_west_texture(clean_line, parse);
		else if (ft_strncmp(clean_line, "EA ", 4) == 0)
			parse_east_texture(clean_line, parse);
		else if (ft_strncmp(clean_line, "F ", 3) == 0)
			parse_floor_colour(clean_line, parse);
		else if (ft_strncmp(clean_line, "C ", 3) == 0)
			parse_ceiling_colour(clean_line, parse);
		line = get_next_line(parse->map_fd);
	}
	if (parse->got_all_elements == true)
		return (0);
	return (1);
}

int	check_map(t_parse *parse)
{
	char	*line;
	int		i;
	int		j;

	parse->start_line = search_start_map(parse->map_fd, parse);
	parse->last_line = search_last_map(parse->map_fd, parse);
	parse->total_map_lines = parse->last_line - parse->start_line + 1;
	parse->map = malloc(sizeof(char *) * (parse->total_map_lines + 1));
	line = get_next_line(parse->map_fd);
	i = 0;
	while (line && i != parse->start_line)
	{
		free(line);
		i++;
		line = get_next_line(parse->map_fd);
	}
	line = save_map(parse, line, i);
	if (is_map_last_in_file(line, parse, i) == false)
		return (1);
	return (0);
}

char	*save_map(t_parse *parse, char *line, int i)
{
	int	j;
	
	j = 0;
	while (line && i != parse->last_line)
	{
		parse->map[j++] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(parse->map_fd);
	}
	parse->map[j] = NULL;
	parse_map(parse);
	return (line);
}

void	parse_map(t_parse *parse)
{

}

bool	is_map_last_in_file(char *line, t_parse *parse, int i)
{
	int	k;

	while (line && i >= parse->last_line)
	{
		k = 0;
		while (line[k])
		{
			if (ft_isalnum(line[k]) == 0)
				return (1);
			k++;
		}
		free(line);
		i++;
		line = get_next_line(parse->map_fd);
	}
	return (0);
}
