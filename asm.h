/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 15:20:14 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/31 15:20:16 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include "libft/libft.h"
# include <sys/stat.h> 
# include <fcntl.h>
# include <stdio.h>

typedef struct 			s_lst
{
	char				*str;
	struct s_lst		*next;
}						t_lst;

typedef struct 			s_asm
{
	char				*bot_name;
	char				*bot_comment;
	struct s_cmnd		*command;
}						t_asm;

typedef struct 			s_cmnd
{
	int					command_name;
	int					t_dir;
	int					t_reg;
	int					t_ind;
	int					n_byte;
	char				*label;
	struct s_cmnd		*next;
}						t_cmnd;

char					*get_name(t_lst **list);
char					*get_comment(t_lst **list);
void					create_file(t_lst *list);

#endif