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
# include "../libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "op.h"

# define SPACES (*l)->str[i] && ((*l)->str[i] == ' ' || (*l)->str[i] == '\t')

typedef struct			s_lst
{
	char				*str;
	int					n_str;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_op
{
	char				*name;
	int					nb_params;
	int					params[3][3];
	int					id;
	int					cycles;
	char				*description;
	int					acb;
	int					label_size;
}						t_op;

typedef struct			s_asm
{
	char				*bot_name;
	char				*bot_comment;
	struct s_cmnd		*command;
	t_op				op_tab[17];
}						t_asm;

typedef struct			s_arg_arr
{
	int					type;
	int					value;
	char				*text;
	int					size;
}						t_arg_arr;

typedef struct			s_args
{
	int					n;
	struct s_arg_arr	arg_arr[3];
}						t_args;

typedef struct			s_cmnd
{
	int					command_name;
	struct s_args		arg;
	int					n_str;
	int					n_byte;
	char				*label;
	struct s_cmnd		*next;
}						t_cmnd;

int						str_comment(char *str);
int						str_name(char *str);
char					*copy_n(char *dst, const char *src, int len, int arg);
char					*copy_n1(char *dst, const char *src, int i, int len);
char					*get_name(t_lst **l, int arg, char *new);
char					*get_comment(t_lst **list);
void					create_file(t_asm a, char *name);

void					get_t_op(t_asm *a);

int						is_command(char *str);

char					*find_label(t_lst **list);
int						find_command_name(t_lst **list, char *label, t_asm *a);
t_args					find_args(t_lst **list, int n_command, t_asm *a, int i);
int						find_label_num(char *str, t_cmnd *cmnds);
int						label_to_numbers(t_cmnd	*cmnds);

void					validation(t_lst **list, t_asm *a);
int						validation_name(t_lst **list, t_asm *a,
						int n_name, int n_comment);
int						validation_commands(t_lst **list, t_asm *a);
int						validation_args(t_cmnd *c, t_asm *a, int i, int j);

void					lst_next(t_lst **list);
void					print_cmnds(t_cmnd	*new);
int						digits(int n);
int						digits_char(char *str);
int						ft_pow(int n, int pow);
int						sum_exec(t_cmnd *c);

void					arg_reg(t_args *t, int j, int *i, t_lst *l);
void					arg_dir(t_args *t, int j, int *i, t_lst *l);
void					arg_ind(t_args *t, int j, int *i, t_lst *l);
void					arg_zero(t_args *t, int j);
int						clean_arg(t_args *t, int j);

char					*get_arg_label(char *str);
int						count_codage(t_args t);
int						find_comma(char *str);

int						a_flag(int argc, char **argv);
void					a_bonus(t_asm a);

#endif
