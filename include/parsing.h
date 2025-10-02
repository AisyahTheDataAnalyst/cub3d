/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:27:28 by aimokhta          #+#    #+#             */
/*   Updated: 2025/10/02 19:29:49 by aimokhta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdbool.h> //bool
# include <fcntl.h> // open

typedef struct s_parse
{
	char	*no_txt;
	char	*so_txt;
	char	*ea_txt;
	char	*we_txt;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_red;
	int		c_green;
	int		c_blue;
	bool	got_all_elements;
	int		start_line;
	int		last_line;
	int		total_map_lines;
	int		map_fd;
	char	**map;

}	t_parse ;

#endif