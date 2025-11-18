/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:20:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/18 10:24:53 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	flood_fill(t_parse *parse, char **dup_map, int row, int col);
// static void	print_dup_map(char **dup_map);
// static void	print_map(t_map *map);

bool	is_map_valid(t_parse *parse, t_player *player, t_map *map)
{
	char	**dup_map;
	int		i;
	bool	ff_status;

	ff_status = false;
	if (!is_player_valid(parse, player, map))
		return (err_msg(parse, INVALID_PLAYER_COUNT), false);
	i = -1;
	dup_map = malloc(sizeof(char *) * (parse->map_height + 1));
	while (map->map[++i])
		dup_map[i] = ft_strdup(map->map[i]);
	dup_map[i] = NULL;
	ff_status = flood_fill(parse,
			dup_map, player->y_pos, player->x_pos);
	if (!ff_status)
		return (free_array(dup_map), err_msg(parse, INVALID_MAP), false);
	return (free_array(dup_map), true);
}

static bool	flood_fill(t_parse *parse, char **dup_map, int row, int col)
{
	if (row < 0 || col < 0
		|| row >= parse->map_height || col >= parse->map_width
		|| col >= (int)ft_strlen(dup_map[row])
		|| skip_whitespace(dup_map[row][col]))
		return (false);
	if (dup_map[row][col] == 'F' || dup_map[row][col] == '1')
		return (true);
	dup_map[row][col] = 'F';
	if (!flood_fill(parse, dup_map, row -1, col)
		|| !flood_fill(parse, dup_map, row, col + 1)
		|| !flood_fill(parse, dup_map, row +1, col)
		|| !flood_fill(parse, dup_map, row, col - 1))
		return (false);
	return (true);
}

// static void	print_map(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	if (!map->map[i])
// 		return (ft_putstr_fd("map is null!\n", 2));
// 	printf("\n2d-array map:\n");
// 	while (map->map[i])
// 	{
// 		ft_putendl_fd(map->map[i], 1);
// 		i++;
// 	}
// 	printf("\n");
// }

// static void	print_dup_map(char **dup_map)
// {
// 	int	i;

// 	i = 0;
// 	if (!dup_map[i])
// 		return (ft_putstr_fd("dup_map is null!\n", 2));
// 	printf("\nmap is flooded:\n");
// 	while (dup_map[i])
// 	{
// 		ft_putendl_fd(dup_map[i], 1);
// 		i++;
// 	}
// 	printf("\n");
// }
