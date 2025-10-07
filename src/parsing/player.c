/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 09:53:28 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 17:28:42 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_player_valid(t_parse *parse)
{
	int	y;
	int	x;
	// int	player_count;

	// player_count = 0;
	y = 0;
	while (parse->map[y])
	{
		printf("y: %d\n", y);
		x = 0;
		while (parse->map[y][x])
		{
			printf("x: %d\n", x);
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
	printf("player_count: %d\n", parse->player_count);
	printf("HELLOOOOOOO\n");
	if (parse->player_count != 1)
		return (parse_err_msg(parse, INVALID_PLAYER), false);
	return (true);
}
