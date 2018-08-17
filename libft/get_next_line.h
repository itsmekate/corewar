/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:12:36 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/07 12:12:38 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFF_SIZE 32

typedef struct		s_lines
{
	int				fd;
	char			*buf;
	struct s_lines	*next;
}					t_lines;

int					get_next_line(const int fd, char **line);

#endif
