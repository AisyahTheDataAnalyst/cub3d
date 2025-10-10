/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:18:51 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/10 15:48:40 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_north_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = 0;
	raw_texture = ft_strtrim(&str[i + 2], " \t\n\r");
	if (++parse->no_txt_count > 1)
		return (free(raw_texture), parse_err_msg(parse, INVALID_NO_COUNT),
			false);
	parse->no_txt = raw_texture;
	if (!accurate_file_type(parse->no_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE_NO), false);
	parse->no_txt_fd = openable_file(parse->no_txt, parse->no_txt_fd);
	if (parse->no_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE), false);
	return (true);
}

bool	parse_south_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = 0;
	raw_texture = ft_strtrim(&str[i + 2], " \t\n\r");
	if (++parse->so_txt_count > 1)
		return (free(raw_texture), parse_err_msg(parse, INVALID_SO_COUNT),
			false);
	parse->so_txt = raw_texture;
	if (!accurate_file_type(parse->so_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE_SO), false);
	parse->so_txt_fd = openable_file(parse->so_txt, parse->ea_txt_fd);
	if (parse->so_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE), false);
	return (true);
}

bool	parse_west_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = 0;
	raw_texture = ft_strtrim(&str[i + 2], " \t\n\r");
	if (++parse->we_txt_count > 1)
		return (free(raw_texture), parse_err_msg(parse, INVALID_WE_COUNT),
			false);
	parse->we_txt = raw_texture;
	if (!accurate_file_type(parse->we_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE_WE), false);
	parse->we_txt_fd = openable_file(parse->we_txt, parse->we_txt_fd);
	if (parse->we_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE), false);
	return (true);
}

bool	parse_east_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = 0;
	raw_texture = ft_strtrim(&str[i + 2], " \t\n\r");
	if (++parse->ea_txt_count > 1)
		return (free(raw_texture), parse_err_msg(parse, INVALID_EA_COUNT),
			false);
	parse->ea_txt = raw_texture;
	if (!accurate_file_type(parse->ea_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE_EA), false);
	parse->ea_txt_fd = openable_file(parse->ea_txt, parse->ea_txt_fd);
	if (parse->ea_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE), false);
	return (true);
}
