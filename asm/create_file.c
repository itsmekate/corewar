/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:03:49 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/27 14:03:51 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		rotate(char *str, int size)
{
	int		i;
	char	tmp;
	int		s;

	i = 0;
	s = size / 2;
	if (size != 1)
		while (size != s)
		{
			tmp = str[i];
			str[i] = str[size - 1];
			str[size - 1] = tmp;
			i++;
			size--;
		}
}

int			count_codage(t_args t)
{
	int		i;
	int		codage;

	i = 0;
	codage = 0;
	while (t.arg_arr[i].type && i < 3)
	{
		if (t.arg_arr[i].type == 1)
			codage += ft_pow(2, 6 - i * 2);
		else if (t.arg_arr[i].type == 2)
			codage += ft_pow(2, 7 - i * 2);
		else if (t.arg_arr[i].type == 3)
			codage += ft_pow(2, 7 - i * 2) + ft_pow(2, 6 - i * 2);
		i++;
	}
	return (codage);
}

void		write_more_commands(int fd, t_cmnd *c, t_asm a)
{
	int		i;
	int		codage;

	codage = 0;
	i = 0;
	if (a.op_tab[c->command_name - 1].acb)
	{
		codage = count_codage(c->arg);
		rotate((char *)&codage, 1);
		write(fd, &codage, 1);
	}
	while ((c->arg.arg_arr[i]).type && i < 3)
	{
		rotate((char *)&c->arg.arg_arr[i].value, c->arg.arg_arr[i].size);
		write(fd, (void *)&c->arg.arg_arr[i].value, c->arg.arg_arr[i].size);
		i++;
	}
}

void		write_commands(int fd, t_cmnd *c, t_asm a)
{
	a.bot_name = NULL;
	while (c)
	{
		if (c->command_name > 0)
			write(fd, (void *)&c->command_name, 1);
		else
		{
			c = c->next;
			continue;
		}
		write_more_commands(fd, c, a);
		c = c->next;
	}
}

void		write_data(int fd, t_asm a)
{
	int		magic;
	char	*zeros;
	int		sum;

	magic = COREWAR_EXEC_MAGIC;
	zeros = ft_memalloc(4);
	sum = sum_exec(a.command);
	rotate((char *)&magic, 4);
	write(fd, &magic, 4);
	write(fd, a.bot_name, PROG_NAME_LENGTH);
	write(fd, zeros, 4);
	rotate((char *)&sum, 4);
	write(fd, &sum, 4);
	write(fd, a.bot_comment, COMMENT_LENGTH);
	write(fd, zeros, 4);
	write_commands(fd, a.command, a);
	free(zeros);
}

void		create_file(t_asm a, char *name)
{
	int		fd;
	char	*file_name;
	char	*tmp_sub;

	file_name = NULL;
	tmp_sub = ft_strsub(name, 0, ft_strlen(name) - 2);
	file_name = ft_strjoin(tmp_sub, ".cor");
	free(tmp_sub);
	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
	write_data(fd, a);
	ft_printf("Writing output program to %s\n", file_name);
	close(fd);
	free(file_name);
}
