/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 12:34:00 by etugoluk          #+#    #+#             */
/*   Updated: 2018/08/11 12:34:01 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			count_bytes(t_cmnd *new, t_asm *a)
{
	int		res;
	int		i;

	res = 1;
	i = 0;
	while (new->arg.arg_arr[i].type)
	{
		if (new->arg.arg_arr[i].type == 1)
			res += 1;
		else if (new->arg.arg_arr[i].type == 2)
			res += a->op_tab[new->command_name - 1].label_size;
		else if (new->arg.arg_arr[i].type == 3)
			res += 2;
		i++;
	}
	if (a->op_tab[new->command_name - 1].acb)
		res++;
	return (res);
}

t_cmnd		*new_command(t_lst **list, t_asm *a)
{
	t_cmnd	*new;

	// printf("%s\n", (*list)->str);
	new = (t_cmnd *)malloc(sizeof(t_cmnd));
	new->label = find_label(list);
	new->n_str = (*list)->n_str;
	if (!(new->command_name = find_command_name(list, new->label, a)))
	{
		free(new);
		ft_printf("Syntax error: wrong command name on line %d\n", (*list)->n_str);
		return (NULL);
	}
	if (new->command_name == -1 && new->label)
	{
		new->n_byte = 0;
		new->next = NULL;
		return (new);
	}
	new->arg = find_args(list, new->command_name, a);
	if (!new->arg.arg_arr[0].type && !validation_args(new, a))
	{
		ft_printf("Syntax error: wrong arguments on line %d\n", (*list)->n_str);
		free(new);
		return (NULL);
	}
	new->n_byte = count_bytes(new, a);
	new->next = NULL;
	return (new);
}


int			validation_commands(t_lst **list, t_asm *a)
{
	t_cmnd	*head;
	t_cmnd	*head_tmp;

	if (!(a->command = new_command(list, a)))
		return (0);
	head = a->command;
	head_tmp = head;
	lst_next(list);
	while ((*list))
	{
		if (!is_command((*list)->str))
		{
			lst_next(list);
			continue;
		}
		if (!(head->next = new_command(list, a)))
			return (0);
		head = head->next;
		lst_next(list);
	}
	if (!label_to_numbers(head_tmp))
		return (0);
	// print_cmnds(head_tmp);
	return (1);
}