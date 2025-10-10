/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:53:28 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/09 10:42:59 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_player_valid(t_parse *parse)
{
	int	y;
	int	x;

	y = 0;
	while (parse->map[y])
	{
		x = 0;
		while (parse->map[y][x])
		{
			if (parse->map[y][x] == 'N' || parse->map[y][x] == 'S'
			|| parse->map[y][x] == 'W' || parse->map[y][x] == 'E')
			{
				parse->player_direction = parse->map[y][x];
				parse->player_count++;
				parse->player_y_pos = y;
				parse->player_x_pos = x;
			}
			x++;
		}
		y++;
	}
	if (parse->player_count != 1)
		return (parse_err_msg(parse, INVALID_PLAYER), false);
	return (true);
}
