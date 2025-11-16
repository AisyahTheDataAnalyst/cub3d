/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:21:49 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/16 16:44:12 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "parsing.h"
# include "../minilibx-linux/mlx.h"
# include <sys/time.h>
# include <math.h>

# define WINDOW_WIDTH 854
# define WINDOW_HEIGHT 480
# define NUM_TEX 4
# define MOVE_CHECK 0.04
# define MOVE_SPEED 0.03

typedef struct s_game	t_game;

// Why is this here?
// typedef struct s_player	t_player;
// typedef struct s_map	t_map;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;

}	t_ray;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}				t_img_data;

typedef struct s_assets
{
	t_img_data	n_wall;
	t_img_data	s_wall;
	t_img_data	e_wall;
	t_img_data	w_wall;
}	t_assets;

typedef struct s_raycast
{
	void		*mlx_connection;
	void		*mlx_window;
	t_img_data	data;
	double		old_time;
	double		time;
	t_assets	assets;
}	t_raycast;

// Need to change this to elsewhere
void	update_player(t_game *game);
void	free_resources(t_game *game);
void	create_window(t_raycast *raycast);
void	create_window_image(t_raycast *raycast);
void	clear_window(t_game *game);
void	sprite_loader(t_game *game);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
int		destroy_window(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	rotate(t_game *game, double rot_speed);
int		handle_input(int keycode, t_game *game);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
int		get_pixel(t_img_data *data, int x, int y);
void	init_step_and_side(t_game *game, t_ray *ray);
void	fill_ceil_floor(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	dda(t_game *game, t_ray *ray);
void	calculate_wall(t_game *game, t_ray *ray);
void	draw_walls(t_game *game, t_ray *ray, int x);

#endif