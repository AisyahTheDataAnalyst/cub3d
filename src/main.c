/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/16 10:20:54 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init(t_game *game);
// static void	print_last_look_map(t_map *map);

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
	// raycasting();
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
