/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_map_details.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:33:03 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/07 16:12:24 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	search_height_start_map\
(t_parse *parse, bool start_flag, int i, char *line);
static bool	search_height_end_map\
(t_parse *parse, int i, int j, char *line);

char	*search_map_details(t_parse *parse)
{
	char	*line;
	int		i;
	int		j;
	bool	start_flag;
	bool	end_flag;

	i = 0;
	start_flag = false;
	end_flag = false;
	line = get_next_line(parse->map_fd);
	printf("im in search map details\n");
	while (line && ++i)
	{
		printf("line= %s\n", line);
		printf("test1\n");
		j = 0;
		printf("i: %d\n", i);
		while (line[j])
		{
			printf("j: %c\n", line[j]);
			printf("test2\n");
			start_flag = search_height_start_map(parse, start_flag, i, line);
			end_flag = search_height_end_map(parse, i, j, line);
			if (end_flag)
				return (line);
			j++;
		}
		free(line);
		line = get_next_line(parse->map_fd);
	}
	return (line);
}

static bool	search_height_start_map\
(t_parse *parse, bool start_flag, int i, char *line)
{
	printf("test3\n");
	if (only_chars_of_map_in_whole_line(line))
	{
		if (start_flag == false)
		{
			parse->height_start = i;
			printf("adjust height_s : %d\n", parse->height_start);
			start_flag = true;
		}
	}
	printf("test3\n");
	return (start_flag);
}

static bool	search_height_end_map\
(t_parse *parse, int i, int j, char *line)
{
	printf("test4\n");
	if (only_chars_of_map_in_whole_line(line) && i >= parse->height_start)
	{
		parse->height_end = i;
		if (is_char_of_map(line[j]))
		{
			if (parse->width_start > j)
				parse->width_start = j;
			if (parse->width_end < j)
				parse->width_end = j;
		}
		return (false);
	}
	if (i < parse->height_start)
		return (false);
	return (true);
}

// int	search_height_end_map(t_parse *parse, int i, int j, char *line)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	line = get_next_line(parse->map_fd);
// 	while (line && i < parse->height_start)
// 	{
// 		free(line);
// 		i++;
// 		line = get_next_line(parse->map_fd);
// 	}
// 	while (line && i >= parse->height_start)
// 	{
// 		i++;
// 		if (!ft_strchr(line, '1') || !ft_strchr(line, '0'))
// 		{
// 			parse->height_end = i;
// 			free(line);
// 			return (i);
// 		}
// 		free(line);
// 		line = get_next_line(parse->map_fd);
// 	}
// 	return (i);
// }

// int	search_map_width(t_parse *parse)
// {
// 	int		curr_line;
// 	int		i;
// 	char	*line;

// 	curr_line = 0;
// 	parse->width_start = INT_MAX;
// 	parse->width_end = -1;
// 	line = get_next_line(parse->map_fd);
// 	while (line && curr_line < parse->height_start)
// 	{
// 		free(line);
// 		curr_line++;
// 		line = get_next_line(parse->map_fd);
// 	}
// 	return (search_map_width_helper_1(parse, line, curr_line, i));
// }

// int	search_map_width_helper_1(t_parse *parse, \
// char *line, char *curr_line, int i)
// {
// 	while (line && curr_line >= parse->height_start
// 		&& curr_line <= parse->height_end)
// 	{
// 		i = 0;
// 		while (line[i])
// 		{
// 			while (skip_whitespace(line[i]))
// 				i++;
// 			if (is_char_of_map(line[i]) && !last_char_of_line(line[i + 1]))
// 				if (parse->width_start > i)
// 					parse->width_start = i;
// 			else if (is_char_of_map(line[i]) && last_char_of_line(line[i + 1]))
// 				if (parse->width_end < i)
// 					parse->width_end = i;
// 			i++;
// 		}
// 		free(line);
// 		curr_line++;
// 		line = get_next_line(parse->map_fd);
// 	}
// 	return (search_map_width_helper_2(parse));
// }

// int	search_map_width_helper_2(t_parse *parse)
// {
// 	parse->map_width = parse->width_end - parse->width_start + 1;
// 	if (parse->map_width < 3)
// 	{
// 		parse->err_msg = INVALID_MAP;
// 		return (-1);
// 	}
// 	return (parse->map_width);
// }
