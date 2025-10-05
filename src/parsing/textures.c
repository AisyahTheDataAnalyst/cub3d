/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:18:51 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 20:53:26 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_north_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;
	char	*to_be_erased;
	int		fd;

	i = 0;
	while (str[i])
		if (str[i] != 'N' && str[i + 1] != 'O')
			i++;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	while (!skip_whitespace(str[i]))
		i++;
	to_be_erased = &str[i];
	parse->no_txt = ft_substr(raw_texture, 0, to_be_erased - raw_texture);
	fd = open(parse->no_txt, O_RDONLY);
	if (fd == -1)
		return (parse_err_msg(INVALID_NO));
	parse->no_txt_flag = true;
	parse->got_all_elements++;
}

void	parse_south_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;
	char	*to_be_erased;
	int		fd;

	i = 0;
	while (str[i])
		if (str[i] != 'S' && str[i + 1] != 'O')
			i++;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	while (!skip_whitespace(str[i]))
		i++;
	to_be_erased = &str[i];
	parse->so_txt = ft_substr(raw_texture, 0, to_be_erased - raw_texture);
	fd = open(parse->so_txt, O_RDONLY);
	if (fd == -1)
		return (parse_err_msg(INVALID_SO));
	parse->so_txt_flag = true;
	parse->got_all_elements++;
}

void	parse_west_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;
	char	*to_be_erased;
	int		fd;

	i = 0;
	while (str[i])
		if (str[i] != 'W' && str[i + 1] != 'E')
			i++;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	while (!skip_whitespace(str[i]))
		i++;
	to_be_erased = &str[i];
	parse->we_txt = ft_substr(raw_texture, 0, to_be_erased - raw_texture);
	fd = open(parse->we_txt, O_RDONLY);
	if (fd == -1)
		return (parse_err_msg(INVALID_WE));
	parse->we_txt_flag = true;
	parse->got_all_elements++;
}

bool	parse_east_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;
	char	*to_be_erased;
	int		fd;

	i = 0;
	while (str[i])
		if (str[i] != 'E' && str[i + 1] != 'A')
			i++;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	while (!skip_whitespace(str[i]))
		i++;
	to_be_erased = &str[i];
	parse->ea_txt = ft_substr(raw_texture, 0, to_be_erased - raw_texture);
	fd = open(parse->ea_txt, O_RDONLY);
	if (fd == -1)
		return (parse_err_msg(INVALID_EA));
	parse->ea_txt_flag = true;
	parse->got_all_elements++;
}
