/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:43:03 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/10 13:17:44 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_char_of_map(char c)
{
	return (c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	only_chars_of_map_in_whole_line(char *line)
{
	int		i;
	bool	map_char_flag;

	if (!line)
		return (0);
	i = 0;
	map_char_flag = 0;
	while (line[i])
	{
		if (is_char_of_map(line[i]))
		{
			map_char_flag = 1;
			i++;
		}
		else if (skip_whitespace(line[i]))
			i++;
		else
			return (-1);
	}
	return (map_char_flag);
}

bool	skip_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

int	char_repitition(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

bool	other_edge_cases_elements(char *str, t_parse *parse)
{
	if (!str)
		return (true);
	parse->not_empty_map = true;
	if (only_chars_of_map_in_whole_line(str) < 0)
	{
		parse->invalid_identifier = true;
		return (false);
	}
	if (only_chars_of_map_in_whole_line(str) == 0)
		return (true);
	if (only_chars_of_map_in_whole_line(str) == 1)
		return (true);
	return (false);
}
