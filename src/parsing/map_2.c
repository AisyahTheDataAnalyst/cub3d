/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:20:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/15 14:04:21 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	flood_fill(t_parse *parse, char **dup_map, int row, int col);

bool	is_map_valid(t_parse *parse, t_player *player, t_map *map)
{
	char	**dup_map;
	int		i;
	bool	ff_status;

	ff_status = false;
	if (!is_player_valid(parse, player, map))
		return (err_msg(parse, INVALID_PLAYER), false);
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

void	map_replace_space_with_wall(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			if (map->map[y][x] == ' ')
				map->map[y][x] = '1';
	}
}

// void	print_map(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!map[i])
// 		return (ft_putstr_fd("map is null!\n", 2));
// 	while (map[i])
// 	{
// 		j = -1;
// 		while (map[i][++j] && map[i][j] != '\n')
// 			printf("%c", map[i][j]);
// 		printf("\n");
// 		i++;
// 	}
// }

// void	print_dup_map(char **dup_map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!dup_map[i])
// 		return (ft_putstr_fd("dup_map is null!\n", 2));
// 	printf("\nflooded:\n");
// 	while (dup_map[i])
// 	{
// 		j = -1;
// 		while (dup_map[i][++j] && dup_map[i][j] != '\n')
// 			printf("%c", dup_map[i][j]);
// 		printf("\n");
// 		i++;
// 	}
// }