#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "parsing.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_player	t_player;
typedef struct s_map	t_map;

typedef struct s_raycast
{
	void	*mlx_connection;
	void	*mlx_window;
}	t_raycast;

void	create_window(t_raycast *raycast);

#endif