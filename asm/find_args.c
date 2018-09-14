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

void		find_more_args(t_lst **list, int *i, int j)
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
	if (j > 2)
	{
		ft_printf("Too much args: line %d\n", (*list)->n_str);
		system("leaks asm");
		exit(0);
	}
}

void		add_i(t_lst **list, int *i, int *j)
{
	*i += digits_char((*list)->str + *i);
	if (find_comma((*list)->str + *i) == -1)
	{
		ft_printf("No comma after arg: line %d\n", (*list)->n_str);
		exit(0);
	}
	else
		(*i) += find_comma((*list)->str + *i);
	(*j)++;
}

t_args		find_args(t_lst **list, int n_command, t_asm *a, int i)
{
	t_args	t;
	int		j;

	j = 0;
	while ((*list)->str[i])
	{
		find_more_args(list, &i, j);
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
		add_i(list, &i, &j);
	}
	while (j < 3)
		arg_zero(&t, j++);
	return (t);
}
