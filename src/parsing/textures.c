/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:18:51 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 13:23:25 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_north_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	printf("done north text!\n");
	i = -1;
	while (str[++i])
		if (str[i] == 'N' && str[i + 1] == 'O')
			break ;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	i = 0;
	while (!skip_whitespace(raw_texture[i]))
		i++;
	if (++parse->no_txt_count > 1)
	{
		printf("notxt: %d\n", parse->no_txt_count);
		return ;
	}
	parse->no_txt = ft_substr(raw_texture, 0, i);
	if (!accurate_file_type(parse->no_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE));
	parse->no_txt_fd = openable_file(parse->no_txt, parse->no_txt_fd);
	if (parse->no_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE));
	close(parse->no_txt_fd);
	printf("done north text!\n");
}

void	parse_south_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = -1;
	while (str[++i])
		if (str[i] == 'S' && str[i + 1] == 'O')
			break ;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	i = 0;
	while (!skip_whitespace(raw_texture[i]))
		i++;
	if (++parse->so_txt_count > 1)
		return ;
	parse->so_txt = ft_substr(raw_texture, 0, i);
	printf("%s\n", parse->so_txt);
	if (!accurate_file_type(parse->so_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE));
	parse->so_txt_fd = openable_file(parse->so_txt, parse->so_txt_fd);
	if (parse->so_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE));
	close(parse->so_txt_fd);
}

void	parse_west_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = -1;
	while (str[++i])
		if (str[i] == 'W' && str[i + 1] == 'E')
			break ;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	i = 0;
	while (!skip_whitespace(raw_texture[i]))
		i++;
	if (++parse->we_txt_count > 1)
		return ;
	parse->we_txt = ft_substr(raw_texture, 0, i);
	if (!accurate_file_type(parse->we_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE));
	parse->we_txt_fd = openable_file(parse->we_txt, parse->we_txt_fd);
	if (parse->we_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE));
	close(parse->we_txt_fd);
}

void	parse_east_texture(char *str, t_parse *parse)
{
	int		i;
	char	*raw_texture;

	i = -1;
	while (str[++i])
		if (str[i] == 'E' && str[i + 1] == 'A')
			break ;
	i++;
	i++;
	while (skip_whitespace(str[i]))
		i++;
	raw_texture = &str[i];
	i = 0;
	while (!skip_whitespace(raw_texture[i]))
		i++;
	if (++parse->ea_txt_count > 1)
		return ;
	parse->ea_txt = ft_substr(raw_texture, 0, i);
	if (!accurate_file_type(parse->ea_txt, ".xpm"))
		return (parse_err_msg(parse, NOT_XPM_FILE));
	parse->ea_txt_fd = openable_file(parse->ea_txt, parse->ea_txt_fd);
	if (parse->ea_txt_fd == -1)
		return (parse_err_msg(parse, UNOPEN_TXT_FILE));
	close(parse->ea_txt_fd);
}
