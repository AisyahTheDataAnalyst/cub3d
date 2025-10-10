/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:39 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/10 15:31:00 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "raycasting.h"

typedef struct s_map
{
	t_parse		*parse;
	t_raycast	*raycast;
}				t_map;

void	all_cleanup(t_map *map);

#endif