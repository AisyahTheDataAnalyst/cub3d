/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:49:26 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 17:50:06 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	flood_fill(t_parse *parse, char player_direction, int row, int col)
{
	if (row < 0 || col < 0
		|| row >= parse->map_height || col >= parse->map_width)
		return ;
	if (parse->map[row][col] == 'F' || parse->map[row][col] == '1'
		|| parse->map[row][col] != player_direction)
		return ;
	parse->map[row][col] = 'F';
	fill(parse, player_direction, row -1, col);
	fill(parse, player_direction, row +1, col);
	fill(parse, player_direction, row, col - 1);
	fill(parse, player_direction, row, col + 1);
}
