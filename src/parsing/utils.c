/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:34:04 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/16 13:07:40 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_parsing(t_parse *parse, char **av)
{
	parse->map_filename = av[1];
	parse->height_start = INT_MAX;
	parse->height_end = -1;
	parse->width_start = INT_MAX;
	parse->width_end = -1;
	parse->map_fd = -1;
	parse->so_txt_fd = -1;
	parse->no_txt_fd = -1;
	parse->we_txt_fd = -1;
	parse->ea_txt_fd = -1;
	parse->elements_status = true;
}

	// printf("err_msg: %s\n", msg);
void	err_msg(t_parse *parse, char *msg)
{
	if (!parse->err_msg)
		parse->err_msg = msg;
}

void	free_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

	// printf("ori_file_type: %s\n", ori_file_type);
	// printf("file_ext: %s\n", file_extension);
bool	accurate_file_type(char *map_filename, char *file_extension)
{
	char	*ori_file_type;

	ori_file_type = ft_strrchr(map_filename, '.');
	if (!ori_file_type || ft_strncmp(ori_file_type, file_extension,
			ft_strlen(file_extension) + 1) != 0)
		return (false);
	return (true);
}

bool	is_space(char c)
{
	return (c == ' ');
}
