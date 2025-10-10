/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/10 15:39:29 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;
	t_parse	parse;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./program maps/map\n", 2), 1);
	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&parse, sizeof(t_parse));
	map.parse = &parse;
	if (parsing(map.parse, av) == 1)
		return (parsing_cleanup(map.parse), 1);
	ft_putendl_fd("Success!", 1);
	// raycasting();
	all_cleanup(&map);
	return (0);
}
