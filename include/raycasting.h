/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:21:49 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/14 16:10:31 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "parsing.h"
# include "../minilibx-linux/mlx.h"
# include <sys/time.h>

typedef struct s_game	t_game;

# define WINDOW_WIDTH 854
# define WINDOW_HEIGHT 480
# define NUM_TEX 4

// Why is this here?
// typedef struct s_player	t_player;
// typedef struct s_map	t_map;

typedef struct s_ray
{
	double cameraX;
	int		mapX;
	int		mapY;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int		color;
}	t_ray;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_img_data;

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
	double		oldTime;
	double		time;
	t_assets	assets;
}	t_raycast;

// Need to change this to elsewhere
void	create_window(t_raycast *raycast);
void	create_window_image(t_raycast *raycast);
void	clear_window(t_game *game);
int		destroy_window(t_game *game);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);
void	draw_ceil_floor(t_game *game);

#endif