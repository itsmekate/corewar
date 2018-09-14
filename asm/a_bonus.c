/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_bonus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:18:17 by etugoluk          #+#    #+#             */
/*   Updated: 2018/09/11 17:18:18 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			a_flag(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-a"))
		{
			if (i != argc - 1)
				return (argc - 1);
			else
				return (i - 1);
		}
		i++;
	}
	return (0);
}

void		cmnd_labl_size(t_cmnd *c, t_asm a, int k)
{
	int				i;
	unsigned char	*n;

	i = 0;
	ft_printf("\n\t\t    ");
	(a.op_tab[c->command_name - 1].acb) ?
		ft_printf("%-4d%-6d", c->command_name, count_codage(c->arg)) :
		ft_printf("%-10d", c->command_name);
	while (c->arg.arg_arr[i].type && i < 3)
	{
		if (c->arg.arg_arr[i].type > 1 && !k)
		{
			n = (unsigned char *)&c->arg.arg_arr[i].value;
			if (a.op_tab[c->command_name - 1].label_size == 2 ||
				c->arg.arg_arr[i].type == 3)
				ft_printf("%-4d%-4d%8c", n[1], n[0], ' ');
			else if (a.op_tab[c->command_name - 1].label_size == 4 &&
				c->arg.arg_arr[i].type == 2)
				ft_printf("%-4d%-4d%-4d%-4d", n[3], n[2], n[1], n[0]);
		}
		else
			ft_printf("%-16d", c->arg.arg_arr[i].value);
		i++;
	}
}

void		print_types(t_cmnd *c)
{
	int		i;

	i = 0;
	while (c->arg.arg_arr[i].type && i < 3)
	{
		if (c->arg.arg_arr[i].type == 1)
			ft_printf("r");
		else if (c->arg.arg_arr[i].type == 2)
			ft_printf("%%");
		if (c->arg.arg_arr[i].text)
			ft_printf(":%-15s", c->arg.arg_arr[i].text);
		else
			(c->arg.arg_arr[i].type == 3) ?
			ft_printf("%-16d", c->arg.arg_arr[i].value) :
			ft_printf("%-15d", c->arg.arg_arr[i].value);
		i++;
	}
}

void		print_commands(t_cmnd *c, t_asm a)
{
	int		sum;

	sum = 0;
	while (c)
	{
		if (c->label)
			ft_printf("%-10d :\t%s:\n", sum, c->label);
		if (c->command_name > 0)
		{
			ft_printf("%-5d(%-3d) :\t    %-10s", sum,
				c->n_byte, a.op_tab[c->command_name - 1].name);
			print_types(c);
			cmnd_labl_size(c, a, 0);
			cmnd_labl_size(c, a, 1);
			ft_printf("\n\n");
		}
		sum += c->n_byte;
		c = c->next;
	}
}

void		a_bonus(t_asm a)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", sum_exec(a.command));
	ft_printf("Name : \"%s\"\n", a.bot_name);
	ft_printf("Comment : \"%s\"\n\n", a.bot_comment);
	print_commands(a.command, a);
}
