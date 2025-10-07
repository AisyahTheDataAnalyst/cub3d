/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:15 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 17:14:44 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	filter_raw_colour(char *raw_colour, t_parse *parse);
static void	save_colour(t_parse *parse, int colour_mode, int *rgb);

void	parse_colour(char *str, t_parse *parse, int colour_mode)
{
	int		i;
	char	*raw_colour;
	char	*temp;
	int		*rgb;

	i = 0;
	printf("str: %s\n", str);
	raw_colour = ft_strtrim(&str[i + 1], " \t\n\r");
	printf("raw_colour: %s\n", raw_colour);
	if (!filter_raw_colour(raw_colour, parse))
		return (free(raw_colour));
	rgb = malloc(sizeof(int) * 3);
	i = -1;
	temp = raw_colour;
	while (temp && ++i < 3)
	{
		// printf("raw_colour: %s\n", raw_colour);
		// printf("i : %d\n", i);
		rgb[i] = ft_atoi(temp);
		// printf("rgb[%d]: %d\n", i, rgb[i]);
		temp = ft_strchr(temp, ',');
		if (temp)
			temp++;
	}
	free(raw_colour);
	save_colour(parse, colour_mode, rgb);
	free(rgb);
}

static bool	filter_raw_colour(char *raw_colour, t_parse *parse)
{
	int		i;
	char	*raw_colour_copy;

	i = -1;
	raw_colour_copy = ft_strdup(raw_colour);
	while (raw_colour_copy[++i])
	{
		if ((i == 0 && ft_isdigit(raw_colour_copy[i]))
			|| (i == (int)ft_strlen(raw_colour_copy) - 1
				&& ft_isdigit(raw_colour_copy[i]))
			|| (char_repitition(raw_colour_copy, ',') == 2
				&& raw_colour_copy[i] == ','
				&& ft_isdigit(raw_colour_copy[i + 1]))
			|| (ft_isdigit(raw_colour_copy[i])))
			continue ;
		else
			return (free(raw_colour_copy),
				parse_err_msg(parse, INVALID_COLOUR), false);
	}
	free(raw_colour_copy);
	return (true);
}

static void	save_colour(t_parse *parse, int colour_mode, int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (parse_err_msg(parse, INVALID_COLOUR));
	if (colour_mode == FLOOR)
	{
		parse->floor_colour = (r < 16 | g < 8 | b);
		parse->floor_count++;
	}
	else if (colour_mode == CEILING)
	{
		parse->ceiling_colour = (r < 16 | g < 8 | b);
		parse->ceiling_count++;
	}
}
