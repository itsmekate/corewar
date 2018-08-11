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
# include "op.h"

typedef struct 			s_lst
{
	char				*str;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_op
{
	char				*name;
	int					nb_params;
	char				params_type[3];
	int					id;
	int					cycles;
	char				*description;
	int					acb;
	int					label_size;
}						t_op;

typedef struct 			s_asm
{
	char				*bot_name;
	char				*bot_comment;
	struct s_cmnd		*command;
	t_op				op_tab[17];
}						t_asm;

typedef struct 			s_arg_arr
{
	int					type;
	int					value;
	char				*text;
}						t_arg_arr;

typedef struct 			s_args
{
	int					n;
	struct s_arg_arr	arg_arr[3];
}						t_args;

typedef struct 			s_cmnd
{
	int					command_name;
	struct s_args		arg;
	int					n_byte;
	char				*label;
	struct s_cmnd		*next;
}						t_cmnd;

char					*get_name(t_lst **list, int k);
char					*get_comment(t_lst **list);
void					create_file(t_lst *list);

void					get_t_op(t_asm *a);

char					*find_label(char *str);
int						find_command_name(char *str, char *label, t_asm *a);
t_args					find_args(char *str, char *label, int n_command, t_asm *a);

int						validation(t_lst **list, t_asm *a);
int						validation_name(t_lst **list, t_asm *a);
int						validation_commands(t_lst **list, t_asm *a);
#endif