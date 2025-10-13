/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/13 13:20:16 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		game;
	t_parse		parse;
	t_player	player;
	t_map		map;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./program maps/map\n", 2), 1);
	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&parse, sizeof(t_parse));
	ft_bzero(&player, sizeof(t_player));
	ft_bzero(&map, sizeof(t_map));
	game.parse = &parse;
	game.player = &player;
	game.map = &map;
	if (parsing(game.parse, game.player, game.map, av) == 1)
		return (parsing_cleanup(game.parse, game.map), 1);
	ft_putendl_fd("Success parsing!", 1);
	// raycasting();
	all_cleanup(&game);
	return (0);
}
