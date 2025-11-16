/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/16 17:06:55 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycast_init(t_game *game)
{
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

int	handle_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		destroy_window(game);
	if (keycode == W_KEY)
		game->keys.w = true;
	if (keycode == S_KEY)
		game->keys.s = true;
	if (keycode == A_KEY)
		game->keys.a = true;
	if (keycode == D_KEY)
		game->keys.d = true;
	if (keycode == LEFT_KEY)
		game->keys.left = true;
	if (keycode == RIGHT_KEY)
		game->keys.right = true;
	return (EXIT_SUCCESS);
}

int	handle_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->keys.w = false;
	if (keycode == S_KEY)
		game->keys.s = false;
	if (keycode == A_KEY)
		game->keys.a = false;
	if (keycode == D_KEY)
		game->keys.d = false;
	if (keycode == LEFT_KEY)
		game->keys.left = false;
	if (keycode == RIGHT_KEY)
		game->keys.right = false;
	return (EXIT_SUCCESS);
}

int	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = -1;
	clear_window(game);
	fill_ceil_floor(game);
	update_player(game);
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
	ft_bzero(&game, sizeof(t_game));
	if (!parsing(&game.parse, &game.player, &game.map, av))
		return (parsing_cleanup(&game.parse, &game.map), 1);
	raycast_init(&game);
	sprite_loader(&game);
	mlx_hook(game.raycast.mlx_window, 2, 1L << 0, handle_press, &game);
	mlx_hook(game.raycast.mlx_window, 3, 1L << 1, handle_release, &game);
	mlx_hook(game.raycast.mlx_window, 17, 1L << 17, destroy_window, &game);
	mlx_loop_hook(game.raycast.mlx_connection, &raycasting, &game);
	mlx_loop(game.raycast.mlx_connection);
	all_cleanup(&game);
	return (0);
}
