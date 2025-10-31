/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:21:49 by yosherau          #+#    #+#             */
/*   Updated: 2025/10/27 15:40:35 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "parsing.h"
// # include "cub3d.h"
# include "../minilibx-linux/mlx.h"

# define WINDOW_WIDTH 854
# define WINDOW_HEIGHT 480

// Why is this here?
// typedef struct s_player	t_player;
// typedef struct s_map	t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_raycast
{
	void	*mlx_connection;
	void	*mlx_window;
	t_data	data;
}	t_raycast;

// Need to change this to elsewhere
void	create_window(t_raycast *raycast);

#endif