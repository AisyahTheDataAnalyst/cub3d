/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/19 22:12:36 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init(t_game *game);
// static void	print_last_look_map(t_map *map);

int	destroy_window(t_game *game)
{
	mlx_destroy_window(game->raycast.mlx_connection, game->raycast.mlx_window);
	mlx_destroy_display(game->raycast.mlx_connection);
	free(game->raycast.mlx_connection);
	exit(EXIT_SUCCESS);
}

	// print_last_look_map(&game.map);
int	main(int ac, char **av)
{
	t_game		game;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./program maps/map\n", 2), 1);
	game_init(&game);
	if (parsing(&game.parse, &game.player, &game.map, av) == 1)
		return (parsing_cleanup(&game.parse, &game.map), 1);
	ft_putendl_fd("Success parsing!", 1);
	raycasting(&game.player, &game.map, &game.raycast);
	mlx_hook(game.raycast.mlx_window, 17, 1L << 17, destroy_window, &game);
	mlx_loop(game.raycast.mlx_connection);
	all_cleanup(&game);
	return (0);
}

static void	game_init(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
}

// static void	print_last_look_map(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	if (!map->map[i])
// 		return (ft_putstr_fd("map is null!\n", 2));
// 	printf("\nfinal look of 2d-array map:\n");
// 	while (map->map[i])
// 	{
// 		ft_putendl_fd(map->map[i], 1);
// 		i++;
// 	}
// 	printf("\n");
// }
