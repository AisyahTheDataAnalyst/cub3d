/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:31:56 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/16 13:05:12 by aimokhta         ###   ########.fr       */
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
	if (line)
		free(line);
	close(parse->map_fd);
	return (true);
}

	// printf("in save map before\n");
	// if (!line)
	// 	printf("line is empty in save map!\n");
		// printf("map i : %d\n", i);
		// printf("map i : %dmap j : %d\n", i, j);
	// printf("in save map after\n");
	// print_map(parse->map);
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

	// printf("len= %d, width= %d\n", len, parse->map_width);
static char	*substring_into_map(char *line, t_parse *parse)
{
	int		len;
	char	*res;

	if (ft_strchr(line, '\n'))
		len = ft_strchr(line, '\n') - (line + parse->width_start);
	else
		len = ft_strchr(line, '\0') - (line + parse->width_start);
	if (parse->map_width > (parse->width_start - len))
		res = ft_substr(line, parse->width_start, len);
	else
		res = ft_substr(line, parse->width_start, parse->map_width);
	return (res);
}

// bool	map_fully_walled(t_parse *parse)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	while (parse->map[y++])
// 	{
// 		x = -1;
// 		while (parse->map[y][x++])
// 		{
// 			if (not_a_wall(parse->map[y][x]) && (
// parse->map[y][x + 1] == ' ' || last_char_of_line(parse->map[y][x + 1]) ||
// parse->map[y][x - 1] == ' ' || x == 0 ||
// parse->map[y + 1][x] == ' ' || last_char_of_line(parse->map[y + 1][x]) ||
// parse->map[y - 1][x] == ' ' || y == 0))
// 				return (false);
// 			else if (not_a_wall(parse->map[x][y]) &&
// 				not_a_wall(parse->map[x + 1][y]) &&
// 				not_a_wall(parse->map[x - 1][y]) &&
// 				not_a_wall(parse->map[x][y + 1]) &&
// 				not_a_wall(parse->map[x][y - 1]))
// 				return (false);
// 		}
// 	}
// 	return (true);
// }
