/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:43:03 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 17:02:37 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_char_of_map(char c)
{
	return (c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	only_chars_of_map_in_whole_line(char *line)
{
	int		i;
	bool	map_char_flag;

	i = 0;
	map_char_flag = false;
	while (line[i])
	{
		if (is_char_of_map(line[i]))
		{
			map_char_flag = true;
			i++;
		}
		else if (skip_whitespace(line[i]))
			i++;
		else
			return (false);
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

// bool	last_char_of_line(char c)
// {
// 	return (c == '\n' || c == '\0');
// }

// bool	not_a_wall(char c)
// {
// 	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
// }