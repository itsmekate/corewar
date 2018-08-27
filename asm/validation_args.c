/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:38:52 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/27 16:38:53 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_label_num(char *str, t_cmnd *cmnds)
{
	int		res;

	res = 0;
	while (cmnds)
	{
		if (cmnds->label)
		{
			if (!strcmp(str, cmnds->label))
				return (res);
		}
		res += cmnds->n_byte;
		cmnds = cmnds->next;
	}
	return (-1);
}

int		label_while(t_cmnd *cmnds, t_cmnd *tmp, int *res)
{
	int	i;
	int	tr;

	i = 0;
	while (cmnds->arg.arg_arr[i].type && i < 3)
	{
		if (cmnds->arg.arg_arr[i].text)
		{
			if ((tr = find_label_num(cmnds->arg.arg_arr[i].text, tmp)) == -1)
			{
				ft_strdel(&cmnds->arg.arg_arr[i].text);
				ft_printf("Syntax error: wrong label argument on line %d\n",
					cmnds->n_str);
				return (0);
			}
			cmnds->arg.arg_arr[i].value = tr - *res;
			ft_strdel(&cmnds->arg.arg_arr[i].text);
		}
		i++;
	}
	*res += cmnds->n_byte;
	return (1);
}

int		label_to_numbers(t_cmnd *cmnds)
{
	t_cmnd	*tmp;
	int		res;

	res = 0;
	tmp = cmnds;
	while (cmnds)
	{
		if (cmnds->command_name == -1)
		{
			cmnds = cmnds->next;
			continue;
		}
		if (!(label_while(cmnds, tmp, &res)))
			return (0);
		cmnds = cmnds->next;
	}
	return (1);
}

int		validation_args(t_cmnd *c, t_asm *a, int i)
{
	int j;

	if (!c->arg.arg_arr[i].type)
		return (0);
	while (c->arg.arg_arr[i].type && i < 3)
	{
		j = 0;
		while (a->op_tab[c->command_name - 1].params[i][j] && j <= 3)
		{
			if (c->arg.arg_arr[i].type ==
				a->op_tab[c->command_name - 1].params[i][j])
				break ;
			else
			{
				j++;
				if (!a->op_tab[c->command_name - 1].params[i][j])
					return (0);
			}
		}
		if (!a->op_tab[c->command_name - 1].params[i][j])
			return (0);
		i++;
	}
	return (1);
}
