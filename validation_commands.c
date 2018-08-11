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

t_cmnd		*new_command(char *str, t_asm *a)
{
	t_cmnd	*new;

	printf("%s\n", str);
	new = (t_cmnd *)malloc(sizeof(t_cmnd));
	new->label = find_label(str);
	if (!(new->command_name = find_command_name(str, new->label, a)))
	{
		free(new);
		return (NULL);
	}
	new->arg = find_args(str, new->label, new->command_name, a);
	// printf("%s %d %d %d %d %d %d %d\n", new->label, new->command_name, new->arg.arg_arr[0].type, new->arg.arg_arr[0].value, new->arg.arg_arr[1].type, new->arg.arg_arr[1].value, new->arg.arg_arr[2].type, new->arg.arg_arr[2].value);
	new->n_byte = 0;
	new->next = NULL;
	return (new);
}

int		validation_commands(t_lst **list, t_asm *a)
{
	t_cmnd	*head;

	if (!(a->command = new_command((*list)->str, a)))
	{
		ft_putendl("Wrong command");
		exit(0);
	}
	head = a->command;
	(*list) = (*list)->next;
	while ((*list))
	{
		if (!is_command((*list)->str))
		{
			(*list) = (*list)->next;
			continue;
		}
		if (!(head->next = new_command((*list)->str, a)))
		{
			ft_putendl("Wrong command");
			exit(0);
		}
		head = head->next;
		(*list) = (*list)->next;
	}
	return (1);
}
