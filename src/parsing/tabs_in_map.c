/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabs_in_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:20:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/10 15:19:03 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 	// while(map[++y])
// 	// x = -1;
// 	// while(map[y][++x])
// 	// true - has chars of map and space only
// 	// else - false
// bool	map_has_valid_chars_only(char **map)
// {
// 	int		y;
// 	int		x;
// 	bool	wall;

// 	wall = false;
// 	y = -1;
// 	while(map[++y])
// 	{
// 		x = -1;
// 		while (map[y][++x])
// 		{
// 			if (map[y][x] == '1')
// 				wall = true;
// 			if (is_char_of_map(map[y][x]) || map[y][x] == ' ')
// 				continue ;
// 			else if ()
// 		}
// 	}
// 	return (true);
// }

// bool	replace_tabs(char **map)
// {
// 	int		y;
// 	int		x;
// 	int		i;
// 	bool	wall;
// 	char	*new_row;
// 	int		total_tabs;

// 	total_tabs = 1;
// 	while (total_tabs)
// 	{
// 		total_tabs = 0;
// 		y = -1;
// 		while (map[++y])
// 		{
// 			total_tabs = char_repitition(map[y], '\t');
// 			if (total_tabs > 0)
// 				break ;
// 			if (only_chars_of_map_in_whole_line(map[y]) == -1)
// 				return (false);
// 		}
// 		if (total_tabs > 0)
// 		{
// 			new_row = malloc(sizeof(char) * (ft_strlen(map[y]) + total_tabs * 3));
// 			x = -1;
// 			while(map[y][++x])
// 			{
// 				i = -1;
// 				if (map[y][x] == '\t')
// 					while (++i <= 3)
// 						new_row[x] = ' ';
// 				new_row[x] = map[y][x];
// 			}
// 		}
// 	}
// 	return (true);
// 	// while(map[++y])
// 	// x = -1;
// 	// while(map[y][++x])
// 	// true - has chars of map and space only
// 	// else - false

// }

void	map_replace_space_with_zero(t_parse *parse)
{
	int	y;
	int	x;

	y = -1;
	while (parse->map[++y])
	{
		x = -1;
		while (parse->map[y][++x])
			if (parse->map[y][x] == ' ')
				parse->map[y][x] = '0';
	}
}
