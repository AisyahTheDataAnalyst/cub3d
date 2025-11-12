/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:21:49 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/12 12:36:55 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "parsing.h"
// # include "cub3d.h"
# include "../minilibx-linux/mlx.h"
# include <sys/time.h>

# define WINDOW_WIDTH 854
# define WINDOW_HEIGHT 480

// Why is this here?
// typedef struct s_player	t_player;
// typedef struct s_map	t_map;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
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
	double		oldTime;
	double		time;
	t_assets	assets;
}	t_raycast;

// Need to change this to elsewhere
void	create_window(t_raycast *raycast);

#endif