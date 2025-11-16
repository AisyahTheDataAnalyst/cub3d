/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:38:09 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/16 16:44:35 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos
		+ game->player.dir_x * MOVE_CHECK)] == '0')
		game->player.x_pos += game->player.dir_x * MOVE_SPEED;
	if (game->map.map[(int)(game->player.y_pos
			+ game->player.dir_y * MOVE_CHECK)][(int)(game->player.x_pos)] == '0')
		game->player.y_pos += game->player.dir_y * MOVE_SPEED;
}

void	move_backward(t_game *game)
{
	if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos
		- game->player.dir_x * MOVE_CHECK)] == '0')
		game->player.x_pos -= game->player.dir_x * MOVE_SPEED;
	if (game->map.map[(int)(game->player.y_pos
			- game->player.dir_y * MOVE_CHECK)][(int)(game->player.x_pos)] == '0')
		game->player.y_pos -= game->player.dir_y * MOVE_SPEED;
}

void	move_left(t_game *game)
{
	if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos
		- game->player.plane_x * MOVE_CHECK)] == '0')
		game->player.x_pos -= game->player.plane_x * MOVE_SPEED;
	if (game->map.map[(int)(game->player.y_pos
			- game->player.plane_y * MOVE_CHECK)][(int)(game->player.x_pos)] == '0')
		game->player.y_pos -= game->player.plane_y * MOVE_SPEED;
}

void	move_right(t_game *game)
{
	if (game->map.map[(int)game->player.y_pos][(int)(game->player.x_pos
		+ game->player.plane_x * MOVE_CHECK)] == '0')
		game->player.x_pos += game->player.plane_x * MOVE_SPEED;
	if (game->map.map[(int)(game->player.y_pos
			+ game->player.plane_y * MOVE_CHECK)][(int)(game->player.x_pos)] == '0')
		game->player.y_pos += game->player.plane_y * MOVE_SPEED;
}

void	rotate(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x
		* cos(rot_speed) - game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(rot_speed) - game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed)
		+ game->player.plane_y * cos(rot_speed);
}
