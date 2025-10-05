/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:15 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 20:29:13 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_colour(char *str, t_parse *parse, int mode)
{
	int		i;
	char	*raw_colour;
	int		*rgb;

	i = 0;
	while (str[i])
		if (str[i] != 'F' || str[i] != 'C')
			i++;
	i++;
	while (!isdigit(str[i]))
		i++;
	raw_colour = &str[i];
	rgb = malloc(sizeof(int) * 3);
	rgb[0] = ft_strdup(ft_atoi(raw_colour));
	raw_colour = ft_strchr(raw_colour, ',') + 1;
	rgb[1] = ft_atoi(raw_colour);
	raw_colour = ft_strchr(raw_colour, ',') + 1;
	rgb[2] = ft_atoi(raw_colour);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
		return (parse_err_msg(INVALID_COLOUR));
	save_colour(parse, mode, rgb);
}

void	save_colour(t_parse *parse, int mode, int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (mode == FLOOR && parse->floor_flag == false)
	{
		parse->floor_colour = (r < 16 | g < 8 | b);
		parse->got_all_elements++;
		parse->floor_flag = true;
	}
	else if (mode == CEILING && parse->ceiling_flag == false)
	{
		parse->ceiling_colour = (r < 16 | g < 8 | b);
		parse->got_all_elements++;
		parse->ceiling_flag = true;
	}
}
