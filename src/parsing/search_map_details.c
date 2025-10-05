/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map_details.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:33:03 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 21:09:08 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	search_start_line_map(t_parse *parse)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(parse->map_fd);
	while (line)
	{
		i++;
		if (ft_strchr(line, '1') || ft_strchr(line, '0'))
		{
			parse->start_line = i;
			free(line);
			return (i);
		}
		free(line);
		line = get_next_line(parse->map_fd);
	}
	return (-1);
}

int	search_last_line_map(t_parse *parse)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(parse->map_fd);
	while (line && i < parse->start_line)
	{
		free(line);
		i++;
		line = get_next_line(parse->map_fd);
	}
	while (line && i >= parse->start_line)
	{
		i++;
		if (!ft_strchr(line, '1') || !ft_strchr(line, '0'))
		{
			parse->last_line = i;
			free(line);
			return (i);
		}
		free(line);
		line = get_next_line(parse->map_fd);
	}
	return (i);
}

int	search_map_width(t_parse *parse)
{
	int		curr_line;
	int		i;
	char	*line;

	curr_line = 0;
	parse->width_start = INT_MAX;
	parse->width_end = -1;
	line = get_next_line(parse->map_fd);
	while (line && curr_line < parse->start_line)
	{
		free(line);
		curr_line++;
		line = get_next_line(parse->map_fd);
	}
	return (search_map_width_helper_1(parse, line, curr_line, i));
}

int	search_map_width_helper_1(t_parse *parse, \
char *line, char *curr_line, int i)
{
	while (line && curr_line >= parse->start_line
		&& curr_line <= parse->last_line)
	{
		i = 0;
		while (line[i])
		{
			while (skip_whitespace(line[i]))
				i++;
			if (is_char_of_map(line[i]) && !last_char_of_line(line[i + 1]))
				if (parse->width_start > i)
					parse->width_start = i;
			else if (is_char_of_map(line[i]) && last_char_of_line(line[i + 1]))
				if (parse->width_end < i)
					parse->width_end = i;
			i++;
		}
		free(line);
		curr_line++;
		line = get_next_line(parse->map_fd);
	}
	return (search_map_width_helper_2(parse));
}

int	search_map_width_helper_2(t_parse *parse)
{
	parse->map_width = parse->width_end - parse->width_start + 1;
	if (parse->map_width < 3)
	{
		parse->err_msg = INVALID_MAP;
		return (-1);
	}
	return (parse->map_width);
}
