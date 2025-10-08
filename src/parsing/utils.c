/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:34:04 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/08 13:22:47 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_err_msg(t_parse *parse, char *msg)
{
	printf("err_msg: %s\n", msg);
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

bool	accurate_file_type(char *map_filename, char *file_extension)
{
	char	*ori_file_type;

	ori_file_type = ft_strrchr(map_filename, '.');
	printf("ori_file_type: %s\n", ori_file_type);
	printf("file_ext: %s\n", file_extension);
	if (!ori_file_type || ft_strncmp(ori_file_type, file_extension,
			ft_strlen(file_extension) + 1) != 0)
		return (false);
	return (true);
}

int	openable_file(char *map_filename, int fd)
{
	fd = open(map_filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	parsing_cleanup(t_parse *parse)
{
	if (parse->so_txt)
		free(parse->so_txt);
	if (parse->no_txt)
		free(parse->no_txt);
	if (parse->we_txt)
		free(parse->we_txt);
	if (parse->ea_txt)
		free(parse->ea_txt);
	if (parse->map)
		free_array(parse->map);
	close(parse->so_txt_fd);
	close(parse->no_txt_fd);
	close(parse->we_txt_fd);
	close(parse->ea_txt_fd);
	close(parse->map_fd);
}
