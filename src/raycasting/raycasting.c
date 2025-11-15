/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:44:35 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/15 21:03:32 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x_pos
				- ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x_pos)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y_pos
				- ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y_pos)
			* ray->delta_dist_y;
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->ray_dir_x = ray->camera_x * game->player.plane_x + game->player.dir_x;
	ray->ray_dir_y = ray->camera_x * game->player.plane_y + game->player.dir_y;
	ray->map_x = (int)game->player.x_pos;
	ray->map_y = (int)game->player.y_pos;
	ray->hit = 0;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	init_step_and_side(game, ray);
}

void	dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] == 49)
			ray->hit = 1;
	}
}

void	calculate_wall(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;
	if (ray->draw_end > WINDOW_HEIGHT)
		ray->draw_end = WINDOW_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.y_pos + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.x_pos + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
}

void	draw_walls(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = ray->draw_start;
	ray->step = 1.0 * 64 / ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2
			+ ray->line_height / 2) * ray->step;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (64 - 1);
		ray->tex_pos += ray->step;
		if (ray->side == 1 && ray->ray_dir_y < 0)
			ray->color = get_pixel(&game->raycast.assets.n_wall,
					ray->tex_x, ray->tex_y);
		else if (ray->side == 1 && ray->ray_dir_y > 0)
			ray->color = get_pixel(&game->raycast.assets.s_wall,
					ray->tex_x, ray->tex_y);
		else if (ray->side == 0 && ray->ray_dir_x > 0)
			ray->color = get_pixel(&game->raycast.assets.e_wall,
					ray->tex_x, ray->tex_y);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			ray->color = get_pixel(&game->raycast.assets.w_wall,
					ray->tex_x, ray->tex_y);
		my_mlx_pixel_put(&game->raycast.data, x, y, ray->color);
		y++;
	}
}
