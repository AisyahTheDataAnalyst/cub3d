/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:43:03 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/05 21:09:08 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing_err_msg(t_parse *parse, char *msg)
{
	if (!parse->err_msg)
		parse->err_msg = msg;
}

bool	is_char_of_map(char c)
{
	return (c == '1' || c == '0'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	not_a_wall(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	skip_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	last_char_of_line(char c)
{
	return (c == '\n' || c == '\0');
}
