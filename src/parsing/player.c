/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:17:16 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/19 10:41:51 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	direction_allocation(t_player *player);
static bool	plane_allocation(t_player *player);
static void	adjust_player_pos(t_player *player, t_map *map);

bool	parse_player(t_player *player, t_map *map)
{
	if (!direction_allocation(player))
		return (false);
	if (!plane_allocation(player))
		return (false);
	adjust_player_pos(player, map);
	return (true);
}

static bool	direction_allocation(t_player *player)
{
	if (player->player_direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		return (true);
	}
	else if (player->player_direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		return (true);
	}
	else if (player->player_direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		return (true);
	}
	else if (player->player_direction == 'E')
	{
		player->dir_x = +1;
		player->dir_y = 0;
		return (true);
	}
	return (false);
}

static bool	plane_allocation(t_player *player)
{
	if (player->player_direction == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
		return (true);
	}
	else if (player->player_direction == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
		return (true);
	}
	else if (player->player_direction == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
		return (true);
	}
	else if (player->player_direction == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
		return (true);
	}
	return (false);
}

static void	adjust_player_pos(t_player *player, t_map *map)
{
	map->map[(int)player->y_pos][(int)player->x_pos] = '0';
	player->y_pos += 0.5;
	player->x_pos += 0.5;
}

bool	is_player_valid(t_parse *parse, t_player *player, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
			|| map->map[y][x] == 'W' || map->map[y][x] == 'E')
			{
				player->player_direction = map->map[y][x];
				parse->player_count++;
				player->y_pos = y;
				player->x_pos = x;
			}
			x++;
		}
		y++;
	}
	if (parse->player_count != 1)
		return (false);
	return (true);
}
