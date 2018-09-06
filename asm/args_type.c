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

int		clean_arg(t_args *t, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		t->arg_arr[i].size = 0;
		t->arg_arr[i].type = 0;
		t->arg_arr[i].value = 0;
		if (t->arg_arr[i].text)
			ft_strdel(&t->arg_arr[i].text);
		i++;
	}
	return (0);
}

int		arg_reg(t_args *t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 1;
	t->arg_arr[j].size = 1;
	if (str[*i + 1] == ':')
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
	else if ((str[*i + 1] >= 48 && str[*i + 1] <= 57) ||
		str[*i + 1] == '-')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(str + *i + 1);
		(*i)++;
		if (t->arg_arr[j].value < 0 || t->arg_arr[j].value > 99)
		{
			ft_putendl("T_REG parameter should be from 0 to 99");
			arg_zero(t, j);
		}
	}
	else
		return (clean_arg(t, j));
	return (1);
}

int		arg_dir(t_args *t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 2;
	if (str[*i + 1] == ':')
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
	else if ((str[*i + 1] >= 48 && str[*i + 1] <= 57) ||
		str[*i + 1] == '-')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(str + *i + 1);
		(*i)++;
	}
	else
		return (clean_arg(t, j));
	return (1);
}

int		arg_ind(t_args *t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 3;
	t->arg_arr[j].size = 2;
	if (str[*i] == ':')
	{
		(*i)++;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
	else if ((str[*i] >= 48 && str[*i] <= 57) ||
		str[*i] == '-')
	{
		t->arg_arr[j].value = ft_atoi(str + *i);
		t->arg_arr[j].text = NULL;
	}
	else
		return (clean_arg(t, j));
	return (1);
}

void	arg_zero(t_args *t, int j)
{
	t->arg_arr[j].size = 0;
	t->arg_arr[j].type = 0;
	t->arg_arr[j].value = 0;
	t->arg_arr[j].text = NULL;
}
