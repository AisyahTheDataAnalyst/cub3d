/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:20:40 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/12 19:56:21 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	is_player_valid(t_parse *parse);
static bool	flood_fill(t_parse *parse, char **dup_map, int row, int col);

bool	is_map_valid(t_parse *parse)
{
	char	**dup_map;
	int		i;
	bool	ff_status;

	ff_status = false;
	if (!is_player_valid(parse))
		return (parse_err_msg(parse, INVALID_PLAYER), false);
	i = -1;
	dup_map = malloc(sizeof(char *) * (parse->map_height + 1));
	while (parse->map[++i])
		dup_map[i] = ft_strdup(parse->map[i]);
	dup_map[i] = NULL;
	ff_status = flood_fill(parse,
			dup_map, parse->player_y_pos, parse->player_x_pos);
	if (!ff_status)
		return (free_array(dup_map), parse_err_msg(parse, INVALID_MAP), false);
	return (free_array(dup_map), true);
}

static bool	is_player_valid(t_parse *parse)
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

void	map_replace_space_with_wall(t_parse *parse)
{
	int	y;
	int	x;

	y = -1;
	while (parse->map[++y])
	{
		x = -1;
		while (parse->map[y][++x])
			if (parse->map[y][x] == ' ')
				parse->map[y][x] = '1';
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