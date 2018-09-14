/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:21:37 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/27 14:21:39 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		find_more_args(t_lst **list, int *i)
{
	while ((*list)->str[*i] && (*list)->str[*i] != '%' &&
		(*list)->str[*i] != 'r' &&
		(*list)->str[*i] != '#' && (*list)->str[*i] != ';' &&
		!ft_isdigit((*list)->str[*i]) &&
		(*list)->str[*i] != '-' && (*list)->str[*i] != ':')
	{
		if ((*list)->str[*i] == ' ' || (*list)->str[*i] == '\t')
			(*i)++;
		else
		{
			ft_printf("Incorrect line: line %d\n", (*list)->n_str);
			system("leaks asm");
			exit(0);
		}
	}
}

int			add_i(t_lst **list, t_args *t, int *i, int *j)
{
	int		tmp;

	*i += digits_char((*list)->str + *i);
	tmp = find_comma((*list)->str + *i);
	if (tmp != 0 && *j > 1)
	{
		ft_printf("Too much args: line %d\n", (*list)->n_str);
		system("leaks asm");
		exit(0);
	}
	if (tmp == -1)
	{
		clean_arg(t, *j + 1);
		return (0);
	}
	else
		(*i) += tmp;
	(*j)++;
	return (1);
}

t_args		find_args(t_lst **list, int n_command, t_asm *a, int i)
{
	t_args	t;
	int		j;

	j = 0;
	while ((*list)->str[i])
	{
		find_more_args(list, &i);
		if ((*list)->str[i] == '%')
		{
			t.arg_arr[j].size = a->op_tab[n_command - 1].label_size;
			arg_dir(&t, j, &i, *list);
		}
		else if ((*list)->str[i] == 'r')
			arg_reg(&t, j, &i, *list);
		else if (ft_isdigit((*list)->str[i]) ||
			(*list)->str[i] == '-' || (*list)->str[i] == ':')
			arg_ind(&t, j, &i, *list);
		else
			break ;
		if (!(add_i(list, &t, &i, &j)))
			return (t);
	}
	while (j < 3)
		arg_zero(&t, j++);
	return (t);
}
