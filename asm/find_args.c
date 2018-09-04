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

int		find_more_args(t_lst **list, t_args *t, int *i)
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
			t->arg_arr[0].type = 0;
			return (0);
		}
	}
	return (1);
}

t_args	return_t(t_args *t, int *j)
{
	if (*j > 3)
	{
		t->arg_arr[0].type = 0;
		return (*t);
	}
	while (*j < 3)
		arg_zero(t, (*j)++);
	return (*t);
}

int		add_i(t_lst **list, t_args *t, int *i, int *j)
{
	*i += digits_char((*list)->str + *i);
	if (find_comma((*list)->str + *i) == -1)
	{
		t->arg_arr[0].type = 0;
		return (0);
	}
	else
		(*i) += find_comma((*list)->str + *i);
	(*j)++;
	return (1);
}

t_args	find_args(t_lst **list, int n_command, t_asm *a, int i)
{
	t_args	t;
	int		j;

	j = 0;
	while ((*list)->str[i])
	{
		if (!(find_more_args(list, &t, &i)))
			return (t);
		if ((*list)->str[i] == '%')
		{
			t.arg_arr[j].size = a->op_tab[n_command - 1].label_size;
			arg_dir(&t, j, &i, (*list)->str);
		}
		else if ((*list)->str[i] == 'r')
			arg_reg(&t, j, &i, (*list)->str);
		else if (ft_isdigit((*list)->str[i]) ||
			(*list)->str[i] == '-' || (*list)->str[i] == ':')
			arg_ind(&t, j, &i, (*list)->str + i);
		else
			break ;
		if (!(add_i(list, &t, &i, &j)))
			return (t);
	}
	return (return_t(&t, &j));
}
