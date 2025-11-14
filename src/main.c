/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/11/14 13:46:56 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	game_init(t_game *game);
// static void	print_last_look_map(t_map *map);

int	handle_input(int keycode, t_game *game)
{
	double	rotSpeed = 0.05;
	if (keycode == ESC_KEY)
		destroy_window(game);
	if (keycode == W_KEY)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos + game->player.dir_x * 0.11)] == '0')
			game->player.x_pos += game->player.dir_x * 0.1;
		if (game->map.map[(int)(game->player.y_pos + game->player.dir_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos += game->player.dir_y * 0.1;
	}
	if (keycode == S_KEY)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos - game->player.dir_x * 0.11)] == '0')
			game->player.x_pos -= game->player.dir_x * 0.1;
		if (game->map.map[(int)(game->player.y_pos - game->player.dir_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos -= game->player.dir_y * 0.1;
	}
	if (keycode == A_KEY)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos - game->player.plane_x * 0.11)] == '0')
			game->player.x_pos -= game->player.plane_x * 0.1;
		if (game->map.map[(int)(game->player.x_pos - game->player.plane_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos -= game->player.plane_y * 0.1;
	}
	if (keycode == D_KEY)
	{
		if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos + game->player.plane_x * 0.11)] == '0')
			game->player.x_pos += game->player.plane_x * 0.1;
		if (game->map.map[(int)(game->player.x_pos + game->player.plane_y * 0.11)][(int)(game->player.x_pos)] == '0')
			game->player.y_pos += game->player.plane_y * 0.1;
	}
	if (keycode == LEFT_KEY)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed);
		game->player.dir_y = oldDirX * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotSpeed) - game->player.plane_y * sin(rotSpeed);
		game->player.plane_y = oldPlaneX * sin(rotSpeed) + game->player.plane_y * cos(rotSpeed);
	}
	if (keycode == RIGHT_KEY)
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

void	load_sprites(void *mlx, char *wall_path, t_img_data *wall)
{
	int	width;
	int	height;

	wall->img = mlx_xpm_file_to_image(mlx, wall_path, &width, &height);
	wall->addr = mlx_get_data_addr(wall->img, &wall->bpp,
			&wall->ll, &wall->endian);
}

void	sprite_loader(t_game *game)
{
	int	index;
	char	*array[NUM_TEX] = {
		game->map.no_txt,
		game->map.we_txt,
		game->map.so_txt,
		game->map.ea_txt,
	};
	t_img_data	*walls[4] = {
		&game->raycast.assets.n_wall,
		&game->raycast.assets.w_wall,
		&game->raycast.assets.s_wall,
		&game->raycast.assets.e_wall
	};

	index = -1;
	while (++index < NUM_TEX)
		load_sprites(game->raycast.mlx_connection, array[index], walls[index]);
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
