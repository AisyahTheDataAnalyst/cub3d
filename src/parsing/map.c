/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:31:56 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/09 11:00:33 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	flood_fill(t_parse *parse, char **dup_map, int row, int col);
// static void	print_map(char **map); // comment later for submission
// static void	print_dup_map(char **dup_map); // comment later for submission

bool	is_map_last_in_file(char *line, t_parse *parse)
{
	if (!line)
	{
		close(parse->map_fd);
		return (true);
	}
	while (line)
	{
		if (only_chars_of_map_in_whole_line(line) == 0)
		{
			free(line);
			line = get_next_line(parse->map_fd);
		}
		else
		{
			free(line);
			close(parse->map_fd);
			return (false);
		}
	}
	close(parse->map_fd);
	return (true);
}

	// printf("in save map before\n");
	// if (!line)
	// 	printf("line is empty in save map!\n");
		// printf("map i : %d\n", i);
		// printf("map i : %dmap j : %d\n", i, j);
	// printf("in save map after\n");
	// print_map(parse->map);
void	save_map(t_parse *parse)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	line = get_next_line(parse->map_fd);
	while (line && ++i < parse->height_start)
	{
		free(line);
		line = get_next_line(parse->map_fd);
	}
	j = 0;
	parse->map = malloc(sizeof(char *) * (parse->map_height + 1));
	while (line && i <= parse->height_end)
	{
		parse->map[j++] = ft_substr(line, parse->width_start, parse->map_width);
		i++;
		free(line);
		line = get_next_line(parse->map_fd);
	}
	if (line)
		free(line);
	parse->map[j] = NULL;
	close(parse->map_fd);
}

	// print_dup_map(dup_map);
bool	is_map_valid(t_parse *parse)
{
	char	**dup_map;
	int		i;
	bool	status;

	if (!is_player_valid(parse))
		return (parse_err_msg(parse, INVALID_PLAYER), false);
	i = -1;
	dup_map = malloc(sizeof(char *) * (parse->map_height + 1));
	while (parse->map[++i])
		dup_map[i] = ft_strdup(parse->map[i]);
	dup_map[i] = NULL;
	status = flood_fill(parse,
			dup_map, parse->player_y_pos, parse->player_x_pos);
	if (!status)
		return (free_array(dup_map), parse_err_msg(parse, INVALID_MAP), false);
	return (free_array(dup_map), true);
}

static bool	flood_fill(t_parse *parse, char **dup_map, int row, int col)
{
	if (row < 0 || col < 0
		|| row >= parse->map_height || col >= parse->map_width
		|| dup_map[row][col] == ' ')
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

// static void	print_map(char **map)
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

// static void	print_dup_map(char **dup_map)
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

//////////////////////////////////////////////////////////////

	// line = get_next_line(parse->map_fd);
	// y = 0;
	// while (line && y++)
	// {
	// 	x = 0;
	// 	while (line[x++])
	// 	{
	// 		if (y <= parse->height_start || y >= parse->height_end
	// 			&& x <= parse->width_start && x >= parse->width_end
	// 			&& line[x] == '0')
	// 			return (parse_err_msg(INVALID_MAP), false);
	// 	}
	// 	free(line);
	// 	line = get_next_line(parse->map_fd);
	// }

// bool	map_fully_walled(t_parse *parse)
// {
// 	int	y;
// 	int	x;

// 	parse->err_msg = INVALID_MAP;
// 	y = -1;
// 	while (parse->map[y++])
// 	{
// 		x = -1;
// 		while (parse->map[y][x++])
// 		{
// 			if (not_a_wall(parse->map[y][x]) && (
// parse->map[y][x + 1] == ' ' || last_char_of_line(parse->map[y][x + 1]) ||
// parse->map[y][x - 1] == ' ' || x == 0 ||
// parse->map[y + 1][x] == ' ' || last_char_of_line(parse->map[y + 1][x]) ||
// parse->map[y - 1][x] == ' ' || y == 0))
// 				return (false);
// 			else if (not_a_wall(parse->map[x][y]) &&
// 				not_a_wall(parse->map[x + 1][y]) &&
// 				not_a_wall(parse->map[x - 1][y]) &&
// 				not_a_wall(parse->map[x][y + 1]) &&
// 				not_a_wall(parse->map[x][y - 1]))
// 				return (false);
// 		}
// 	}
// 	return (true);
// }

// bool	is_map_last_in_file(char *line, t_parse *parse, int i)
// {
// 	int	k;

// 	while (line && i > parse->height_end)
// 	{
// 		k = 0;
// 		while (line[k])
// 		{
// 			if (ft_isalnum(line[k]) == 0)
// 			{
// 				parse->err_msg = MAP_IS_NOT_LAST;
// 				return (false);
// 			}
// 			k++;
// 		}
// 		free(line);
// 		i++;
// 		line = get_next_line(parse->map_fd);
// 	}
// 	return (true);
// }
