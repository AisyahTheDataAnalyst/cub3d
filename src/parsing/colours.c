/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:15 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/08 19:56:48 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	filter_raw_colour(char *raw_colour, t_parse *parse);
static bool	save_colour(t_parse *parse, int colour_mode, int *rgb);
static bool	have_space_between_numbers(char *colour);

bool	parse_colour(char *str, t_parse *parse)
{
	int		i;
	char	*raw_colour;
	char	*temp;
	int		*rgb;
	int		colour_mode;

	i = 0;
	if (str[i] == 'F')
		colour_mode = FLOOR;
	else
		colour_mode = CEILING;
	raw_colour = ft_strtrim(&str[i + 1], " \t\n\r");
	if (!filter_raw_colour(raw_colour, parse))
		return (free(raw_colour), false);
	rgb = malloc(sizeof(int) * 3);
	i = -1;
	temp = raw_colour;
	while (temp && ++i < 3)
	{
		rgb[i] = ft_atoi(temp);
		temp = ft_strchr(temp, ',');
		if (temp)
			temp++;
	}
	return (free(raw_colour), save_colour(parse, colour_mode, rgb));
}

static bool	filter_raw_colour(char *raw_colour, t_parse *parse)
{
	int		i;

	if (have_space_between_numbers(raw_colour))
		return (parse_err_msg(parse, INVALID_COLOUR), false);
	i = -1;
	while (raw_colour[++i])
	{
		if ((i == 0 && ft_isdigit(raw_colour[i]))
			|| (i == (int)ft_strlen(raw_colour) - 1
				&& ft_isdigit(raw_colour[i]))
			|| char_repitition(raw_colour, ',') == 2
			|| (ft_isdigit(raw_colour[i]))
			|| skip_whitespace(raw_colour[i])
			|| raw_colour[i] == ',')
			continue ;
		else
			return (parse_err_msg(parse, INVALID_COLOUR), false);
	}
	return (true);
}

static bool	have_space_between_numbers(char *colour)
{
	int	i;

	i = 0;
	while (colour[i])
	{
		while (colour[i] && ft_isdigit(colour[i]))
			i++;
		while (colour[i] && skip_whitespace(colour[i]))
			i++;
		if (colour[i] && ft_isdigit(colour[i]))
			return (true);
		if (colour[i] && colour[i] == ',')
			i++;
		while (colour[i] && skip_whitespace(colour[i]))
			i++;		
	}
	return (false);
}
// 999           ,            9        ,        9
// 99    9       ,      9              ,        9        9

static bool	save_colour(t_parse *parse, int colour_mode, int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (parse_err_msg(parse, INVALID_COLOUR), false);
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
	if (parse->floor_count > 1)
		return (free(rgb), parse_err_msg(parse, INVALID_FLOOR_COUNT), false);
	if (parse->ceiling_count > 1)
		return (free(rgb), parse_err_msg(parse, INVALID_CEILING_COUNT), false);
	return (free(rgb), true);
}
