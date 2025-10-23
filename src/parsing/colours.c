/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysheraun <ysheraun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:15 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/22 15:19:57 by ysheraun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	filter_raw_colour(char *raw_colour, t_parse *parse);
static bool	save_colour(t_parse *parse, t_map *map);
static bool	have_space_between_numbers(char *colour);

bool	parse_colour(char *str, t_parse *parse, t_map *map)
{
	int		i;
	char	*raw_colour;
	char	*temp;

	i = 0;
	if (str[i] == 'C')
		parse->colour_mode = CEILING;
	while (++i && is_space(str[i]))
		continue ;
	if (skip_whitespace(str[i]) && !is_space(str[i]))
		return (err_msg(parse, NOT_SPACE), false);
	raw_colour = ft_strtrim(&str[i], " \t\n");
	if (!filter_raw_colour(raw_colour, parse))
		return (free(raw_colour), false);
	parse->rgb = malloc(sizeof(int) * 3);
	i = -1;
	temp = raw_colour;
	while (temp && ++i < 3)
	{
		parse->rgb[i] = ft_atoi(temp);
		temp = ft_strchr(temp, ',');
		if (temp)
			temp++;
	}
	return (free(raw_colour), save_colour(parse, map));
}

static bool	filter_raw_colour(char *raw_colour, t_parse *parse)
{
	int		i;

	if (have_space_between_numbers(raw_colour)
		|| char_repitition(raw_colour, ',') != 2)
		return (err_msg(parse, INVALID_COLOUR), false);
	i = -1;
	while (raw_colour[++i])
	{
		if ((i == 0 && ft_isdigit(raw_colour[i]))
			|| (i == (int)ft_strlen(raw_colour) - 1
				&& ft_isdigit(raw_colour[i]))
			|| ft_isdigit(raw_colour[i])
			|| skip_whitespace(raw_colour[i])
			|| raw_colour[i] == ','
			|| (raw_colour[i] == '+' && i == 0)
			|| (raw_colour[i] == '+' && i > 0
				&& (raw_colour[i - 1] == ' ' || (raw_colour[i - 1] == ','))))
			continue ;
		else
			return (err_msg(parse, INVALID_COLOUR), false);
	}
	return (true);
}

static bool	have_space_between_numbers(char *colour)
{
	int	i;

	i = 0;
	while (colour[i])
	{
		while (colour[i] && (colour[i] == '-' || colour[i] == '+'))
			i++;
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
// valid	:	999           ,            9        ,        9
// invalid	:	99    9       ,            9        ,        9        9

		// printf("floor_c : %d\n", parse->floor_count);
		// printf("ceiling_c : %d\n", parse->ceiling_count);
static bool	save_colour(t_parse *parse, t_map *map)
{
	int	r;
	int	g;
	int	b;

	r = parse->rgb[0];
	g = parse->rgb[1];
	b = parse->rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free(parse->rgb), err_msg(parse, INVALID_COLOUR), false);
	if (parse->colour_mode == FLOOR)
	{
		map->floor_colour = (r << 16 | g << 8 | b);
		parse->floor_count++;
	}
	else if (parse->colour_mode == CEILING)
	{
		map->ceiling_colour = (r << 16 | g << 8 | b);
		parse->ceiling_count++;
	}
	parse->colour_mode = 0;
	if (parse->floor_count > 1)
		return (free(parse->rgb), err_msg(parse, INVALID_FLOOR_COUNT), false);
	if (parse->ceiling_count > 1)
		return (free(parse->rgb), err_msg(parse, INVALID_CEILING_COUNT), false);
	return (free(parse->rgb), true);
}
