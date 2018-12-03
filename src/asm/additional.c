/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:00:05 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/27 14:00:07 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	lst_next(t_lst **list)
{
	t_lst	*tmp;

	if (*list)
	{
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp->str);
		free(tmp);
	}
}

int		digits(int n)
{
	int			size;
	int			i;

	size = 1;
	i = 1;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

int		digits_char(char *str, t_args t, int j)
{
	int		i;

	i = 0;
	if (t.arg_arr[j].text)
	{
		while (ft_strchr(LABEL_CHARS, str[i]))
			i++;
	}
	else
	{
		if (str[i] == '-')
			i++;
		while (ft_isdigit(str[i]))
			i++;
	}
	return (i);
}

int		ft_pow(int n, int pow)
{
	int		result;
	int		i;

	result = 1;
	i = 0;
	if (pow < 0)
		return (0);
	while (i++ < pow)
	{
		result *= n;
	}
	return (result);
}

int		sum_exec(t_cmnd *c)
{
	int		res;

	res = 0;
	while (c)
	{
		res += c->n_byte;
		c = c->next;
	}
	return (res);
}
