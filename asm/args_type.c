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

void	arg_reg(t_args *t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 1;
	t->arg_arr[j].size = 1;
	if (str[*i + 1] != ':')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(str + *i + 1);
		(*i)++;
	}
	else
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
}

void	arg_dir(t_args *t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 2;
	if (str[*i + 1] != ':')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(str + *i + 1);
		(*i)++;
	}
	else
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
}

void	arg_ind(t_args *t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 3;
	t->arg_arr[j].size = 2;
	if (*str == ':')
	{
		(*i)++;
		t->arg_arr[j].text = get_arg_label(str + 1);
		t->arg_arr[j].value = 0;
	}
	else
	{
		t->arg_arr[j].value = ft_atoi(str);
		t->arg_arr[j].text = NULL;
	}
}

void	arg_zero(t_args *t, int j)
{
	t->arg_arr[j].size = 0;
	t->arg_arr[j].type = 0;
	t->arg_arr[j].value = 0;
	t->arg_arr[j].text = NULL;
}
