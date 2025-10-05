/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:31:56 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 20:30:42 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*save_map(t_parse *parse, char *line, int i)
{
	int	j;

	j = 0;
	while (line && i <= parse->last_line)
	{
		parse->map[j++] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(parse->map_fd);
	}
	parse->map[j] = NULL;
	return (line);
}

void	map_replace_space_with_zero(t_parse *parse)
{
	int	y;
	int	x;

	y = -1;
	while (parse->map[y++])
	{
		x = -1;
		while (parse->map[y][x++])
			if (parse->map[y][x] == ' ')
				parse->map[y][x] == '0';
	}
}

bool	map_fully_walled(t_parse *parse)
{
	int	y;
	int	x;

	parse->err_msg = INVALID_MAP;
	y = -1;
	while (parse->map[y++])
	{
		x = -1;
		while (parse->map[y][x++])
		{
			if (not_a_wall(parse->map[y][x]) && (\
parse->map[y][x + 1] == ' ' || last_char_of_line(parse->map[y][x + 1]) || \
parse->map[y][x - 1] == ' ' || x == 0 || \
parse->map[y + 1][x] == ' ' || last_char_of_line(parse->map[y + 1][x]) || \
parse->map[y - 1][x] == ' ' || y == 0))
				return (false);
			else if (not_a_wall(parse->map[x][y]) &&
				not_a_wall(parse->map[x + 1][y]) &&
				not_a_wall(parse->map[x - 1][y]) &&
				not_a_wall(parse->map[x][y + 1]) &&
				not_a_wall(parse->map[x][y - 1]))
				return (false);
		}
	}
	return (true);
}

bool	is_map_valid(t_parse *parse)
{
	int	x;
	int	y;

	flood_fill(parse, parse->player_direction,
		parse->player_row, parse->player_col);
	x = 0;
	while (parse->map[x])
	{
		y = 0;
		while (parse->map[x][y])
		{
			if (parse->map[x][y] == '0')
			{
				parse->err_msg = INVALID_MAP;
				return (false);
			}
			y++;
		}
		x++;
	}
	return (true);
}

bool	is_map_last_in_file(char *line, t_parse *parse, int i)
{
	int	k;

	while (line && i > parse->last_line)
	{
		k = 0;
		while (line[k])
		{
			if (ft_isalnum(line[k]) == 0)
			{
				parse->err_msg = MAP_IS_NOT_LAST;
				return (false);
			}
			k++;
		}
		free(line);
		i++;
		line = get_next_line(parse->map_fd);
	}
	return (true);
}
