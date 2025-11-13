/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/13 16:44:21 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	game_init(t_game *game);
// static void	print_last_look_map(t_map *map);

int	destroy_window(t_game *game)
{
	mlx_destroy_window(game->raycast.mlx_connection, game->raycast.mlx_window);
	mlx_destroy_display(game->raycast.mlx_connection);
	free(game->raycast.mlx_connection);
	all_cleanup(game);
	exit(EXIT_SUCCESS);
}

int	handle_input(int keycode, t_game *game)
{
	double rotSpeed = 0.05;
	if (keycode == 65307)
		destroy_window(game);
	if (keycode == 119)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos + game->player.dir_x * 0.11)] == '0')
			game->player.x_pos += game->player.dir_x * 0.1;
		if (game->map.map[(int)(game->player.y_pos + game->player.dir_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos += game->player.dir_y * 0.1;
	}
	if (keycode == 115)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos - game->player.dir_x * 0.11)] == '0')
			game->player.x_pos -= game->player.dir_x * 0.1;
		if (game->map.map[(int)(game->player.y_pos - game->player.dir_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos -= game->player.dir_y * 0.1;
	}
	if (keycode == 97)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos - game->player.plane_x * 0.11)] == '0')
			game->player.x_pos -= game->player.plane_x * 0.1;
		if (game->map.map[(int)(game->player.x_pos - game->player.plane_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos -= game->player.plane_y * 0.1;
	}
	if (keycode == 100)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos + game->player.plane_x * 0.11)] == '0')
			game->player.x_pos += game->player.plane_x * 0.1;
		if (game->map.map[(int)(game->player.x_pos + game->player.plane_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos += game->player.plane_y * 0.1;
	}
	if (keycode == 65363)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed);
		game->player.dir_y = oldDirX * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotSpeed) - game->player.plane_y * sin(rotSpeed);
		game->player.plane_y = oldPlaneX * sin(rotSpeed) + game->player.plane_y * cos(rotSpeed);
	}
	if (keycode == 65361)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rotSpeed) - game->player.dir_y * sin(-rotSpeed);
		game->player.dir_y = oldDirX * sin(-rotSpeed) + game->player.dir_y * cos(-rotSpeed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rotSpeed) - game->player.plane_y * sin(-rotSpeed);
		game->player.plane_y = oldPlaneX * sin(-rotSpeed) + game->player.plane_y * cos(-rotSpeed);
	}
	return (EXIT_SUCCESS);
}

// print_last_look_map(&game.map);
int	main(int ac, char **av)
{
	t_game		game;
	int			width;
	int			height;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./program maps/map\n", 2), 1);
	game_init(&game);
	if (parsing(&game.parse, &game.player, &game.map, av) == 1)
		return (parsing_cleanup(&game.parse, &game.map), 1);
	ft_putendl_fd("Success parsing!", 1);
	game.raycast.assets.n_wall.img = mlx_xpm_file_to_image(game.raycast.mlx_connection, game.map.no_txt, &width, &height);
	game.raycast.assets.n_wall.addr = mlx_get_data_addr(game.raycast.assets.n_wall.img, &game.raycast.assets.n_wall.bpp, &game.raycast.assets.n_wall.ll, &game.raycast.assets.n_wall.endian);
	game.raycast.assets.s_wall.img = mlx_xpm_file_to_image(game.raycast.mlx_connection, game.map.so_txt, &width, &height);
	game.raycast.assets.s_wall.addr = mlx_get_data_addr(game.raycast.assets.s_wall.img, &game.raycast.assets.s_wall.bpp, &game.raycast.assets.s_wall.ll, &game.raycast.assets.s_wall.endian);
	game.raycast.assets.e_wall.img = mlx_xpm_file_to_image(game.raycast.mlx_connection, game.map.ea_txt, &width, &height);
	game.raycast.assets.e_wall.addr = mlx_get_data_addr(game.raycast.assets.e_wall.img, &game.raycast.assets.e_wall.bpp, &game.raycast.assets.e_wall.ll, &game.raycast.assets.e_wall.endian);
	game.raycast.assets.w_wall.img = mlx_xpm_file_to_image(game.raycast.mlx_connection, game.map.we_txt, &width, &height);
	game.raycast.assets.w_wall.addr = mlx_get_data_addr(game.raycast.assets.w_wall.img, &game.raycast.assets.w_wall.bpp, &game.raycast.assets.w_wall.ll, &game.raycast.assets.w_wall.endian);
	mlx_hook(game.raycast.mlx_window, 2, 1L << 0, handle_input, &game);
	mlx_hook(game.raycast.mlx_window, 17, 1L << 17, destroy_window, &game);
	mlx_loop_hook(game.raycast.mlx_connection, &raycasting, &game);
	mlx_loop(game.raycast.mlx_connection);
	all_cleanup(&game);
	return (0);
}

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
