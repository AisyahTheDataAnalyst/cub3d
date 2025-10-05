/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:57:27 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 21:06:16 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_valid_player(t_parse *parse)
{
	int	y;
	int	x;

	y = -1;
	while (parse->map[y++])
	{
		x = -1;
		while (parse->map[y][x++])
			if (parse->map[y][x] == 'N' || parse->map[y][x] == 'S'
			|| parse->map[y][x] == 'W' || parse->map[y][x] == 'E')
				parse->player_count++;
	}
	if (parse->player_count != 1)
		return (parse_err_msg(MANY_PLAYERS), false);
	return (true);
}
