/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:26:25 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 17:31:32 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_parse	parse;

	if (ac != 2)
		return (ft_putstr_fd("Usage: ./program maps/map\n", 2), 1);
	ft_bzero(&parse, sizeof(t_parse));
	if (parsing(&parse, av) == 1)
		return (parsing_cleanup(&parse), 1);
	ft_putendl_fd("Success!", 1);
	// raycasting();
	// all_cleaup(&parse);
	parsing_cleanup(&parse); // delelte later coz its apart of all_cleanup
	return (0);
}
