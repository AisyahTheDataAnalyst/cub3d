/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:52:57 by yosherau          #+#    #+#             */
/*   Updated: 2025/10/19 21:59:35 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

# define WINDOW_WIDTH 854
# define WINDOW_HEIGHT 480

void	create_window(t_raycast *raycast)
{
	raycast->mlx_connection = mlx_init();
	raycast->mlx_window = mlx_new_window(raycast->mlx_connection,
		WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
}