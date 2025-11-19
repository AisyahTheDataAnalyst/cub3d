/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:31:56 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/19 10:39:57 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*substring_into_map(char *line, t_parse *parse);

bool	is_map_last_in_file(char *line, t_parse *parse)
{
	if (!line)
	{
		close(parse->map_fd);
		return (true);
	}
	while (line)
	{
		if (only_chars_of_map_and_whitespace_in_whole_line(line) == 0)
		{
			free(line);
			line = get_next_line(parse->map_fd);
		}
		else
		{
			free(line);
			close(parse->map_fd);
			return (false);
		}
	}
	close(parse->map_fd);
	return (true);
}

bool	map_has_valid_chars_only(t_parse *parse)
{
	int		i;
	char	*line;

	parse->map_fd = open(parse->map_filename, O_RDONLY);
	if (parse->map_fd == -1)
		return (err_msg(parse, UNOPEN_MAP_FILE), false);
	i = 0;
	line = get_next_line(parse->map_fd);
	while (line && ++i < parse->height_start)
	{
		free(line);
		line = get_next_line(parse->map_fd);
	}
	while (line && i++ <= parse->height_end)
	{
		if (only_chars_of_map_in_whole_line(line) == -1)
			return (free(line), close(parse->map_fd),
				err_msg(parse, INVALID_MAP), false);
		free(line);
		line = get_next_line(parse->map_fd);
	}
	line = get_next_line(-2);
	free(line);
	close(parse->map_fd);
	return (true);
}

void	save_map(t_parse *parse, t_map *map)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	line = get_next_line(parse->map_fd);
	while (line && ++i < parse->height_start)
	{
		free(line);
		line = get_next_line(parse->map_fd);
	}
	j = 0;
	map->map = malloc(sizeof(char *) * (parse->map_height + 1));
	while (line && i <= parse->height_end)
	{
		map->map[j++] = substring_into_map(line, parse);
		i++;
		free(line);
		line = get_next_line(parse->map_fd);
	}
	if (line)
		free(line);
	map->map[j] = NULL;
	close(parse->map_fd);
}

static char	*substring_into_map(char *line, t_parse *parse)
{
	int		len;
	char	*end;
	char	*res;

	end = ft_strchr(line, '\n');
	if (!end)
		end = ft_strchr(line, '\0');
	len = end - &line[parse->width_start];
	if (parse->map_width > len)
		res = ft_substr(line, parse->width_start, len);
	else
		res = ft_substr(line, parse->width_start, parse->map_width);
	return (res);
}
