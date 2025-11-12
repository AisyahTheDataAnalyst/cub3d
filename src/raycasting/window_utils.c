/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosherau <yosherau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 21:52:57 by yosherau          #+#    #+#             */
/*   Updated: 2025/11/12 15:22:15 by yosherau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	create_window(t_raycast *raycast)
{
	raycast->mlx_connection = mlx_init();
	raycast->mlx_window = mlx_new_window(raycast->mlx_connection,
		WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
}

void	create_window_image(t_raycast *raycast)
{
	raycast->data.img = mlx_new_image(raycast->mlx_connection, WINDOW_WIDTH, WINDOW_HEIGHT);
	raycast->data.addr = mlx_get_data_addr(raycast->data.img, &raycast->data.bpp,
		&raycast->data.ll, &raycast->data.endian);
}
