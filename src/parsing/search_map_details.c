/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map_details.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:33:03 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/16 13:06:21 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	search_height_start_map\
(t_parse *parse, bool found_start, int i, char *line);
static bool	search_height_end_map\
(t_parse *parse, int i, int j, char *line);

char	*search_map_details(t_parse *parse)
{
	char	*line;
	int		i;
	int		j;
	bool	found_start;
	bool	found_end;

	i = 0;
	found_start = false;
	found_end = false;
	line = get_next_line(parse->map_fd);
	while (line && ++i)
	{
		j = 0;
		while (line[j])
		{
			found_start = search_height_start_map(parse, found_start, i, line);
			found_end = search_height_end_map(parse, i, j, line);
			if (found_end)
				return (line);
			j++;
		}
		free(line);
		line = get_next_line(parse->map_fd);
	}
	return (line);
}

static bool	search_height_start_map\
(t_parse *parse, bool found_start, int i, char *line)
{
	if (only_chars_of_map_and_whitespace_in_whole_line(line) == 1)
	{
		if (found_start == false)
		{
			parse->height_start = i;
			found_start = true;
		}
	}
	return (found_start);
}

static bool	search_height_end_map\
(t_parse *parse, int i, int j, char *line)
{
	if (only_chars_of_map_and_whitespace_in_whole_line(line) == 1
		&& i >= parse->height_start)
	{
		parse->height_end = i;
		if (is_char_of_map(line[j]))
		{
			if (parse->width_start > j)
				parse->width_start = j;
			if (parse->width_end < j)
				parse->width_end = j;
		}
		return (false);
	}
	if (i < parse->height_start)
		return (false);
	return (true);
}
