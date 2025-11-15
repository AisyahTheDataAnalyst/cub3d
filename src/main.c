/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/15 21:03:04 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	game_init(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	create_window(&game->raycast);
	create_window_image(&game->raycast);
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

int	handle_input(int keycode, t_game *game)
{
	const double	rot_speed = 0.05;

	if (keycode == 65307)
		destroy_window(game);
	if (keycode == 119)
		move_forward(game);
	if (keycode == 115)
		move_backward(game);
	if (keycode == 97)
		move_left(game);
	if (keycode == 100)
		move_right(game);
	if (keycode == 65363)
		rotate(game, rot_speed);
	if (keycode == 65361)
		rotate(game, -rot_speed);
	return (EXIT_SUCCESS);
}

int	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	clear_window(game);
	fill_ceil_floor(game);
	while (++x < WINDOW_WIDTH)
	{
		init_ray(game, &ray, x);
		dda(game, &ray);
		calculate_wall(game, &ray);
		draw_walls(game, &ray, x);
	}
	mlx_put_image_to_window(game->raycast.mlx_connection,
		game->raycast.mlx_window, game->raycast.data.img, 0, 0);
	return (EXIT_SUCCESS);
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
	sprite_loader(&game);
	mlx_hook(game.raycast.mlx_window, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.raycast.mlx_window, 17, 1L << 17, destroy_window, &game);
	mlx_loop_hook(game.raycast.mlx_connection, &raycasting, &game);
	mlx_loop(game.raycast.mlx_connection);
	all_cleanup(&game);
	return (0);
}
