/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:40:27 by etugoluk          #+#    #+#             */
/*   Updated: 2018/09/04 17:40:27 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		arg_reg(t_args *t, int j, int *i, t_lst *l)
{
	t->arg_arr[j].type = 1;
	t->arg_arr[j].size = 1;
	if ((l->str[*i + 1] >= 48 && l->str[*i + 1] <= 57) ||
		l->str[*i + 1] == '-')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(l->str + *i + 1);
		(*i)++;
		if (t->arg_arr[j].value < 0 || t->arg_arr[j].value > 99)
		{
			ft_printf("T_REG arg should be from 0 to 99: line %d", l->n_str);
			exit(0);
		}
	}
	else
	{
		ft_printf("Bad T_REG arg: line %d\n", l->n_str);
		exit(0);
	}
}

void		arg_dir(t_args *t, int j, int *i, t_lst *l)
{
	t->arg_arr[j].type = 2;
	if (l->str[*i + 1] == ':')
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(l->str + *i);
		t->arg_arr[j].value = 0;
	}
	else if ((l->str[*i + 1] >= 48 && l->str[*i + 1] <= 57) ||
		l->str[*i + 1] == '-')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(l->str + *i + 1);
		(*i)++;
	}
	else
	{
		ft_printf("Bad T_DIR arg: line %d\n", l->n_str);
		exit(0);
	}
}

void		arg_ind(t_args *t, int j, int *i, t_lst *l)
{
	t->arg_arr[j].type = 3;
	t->arg_arr[j].size = 2;
	if (l->str[*i] == ':')
	{
		(*i)++;
		t->arg_arr[j].text = get_arg_label(l->str + *i);
		t->arg_arr[j].value = 0;
	}
	else if ((l->str[*i] >= 48 && l->str[*i] <= 57) ||
		l->str[*i] == '-')
	{
		t->arg_arr[j].value = ft_atoi(l->str + *i);
		t->arg_arr[j].text = NULL;
	}
	else
	{
		ft_printf("Bad T_IND arg: line %d\n", l->n_str);
		exit(0);
	}
}

void		arg_zero(t_args *t, int j)
{
	t->arg_arr[j].size = 0;
	t->arg_arr[j].type = 0;
	t->arg_arr[j].value = 0;
	t->arg_arr[j].text = NULL;
}
