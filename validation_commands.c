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

// int			count_bytes(t_cmnd *new)
// {
// 	int res;

// 	res = 1;
// 	return (res);
// }

t_cmnd		*new_command(t_lst **list, t_asm *a)
{
	t_cmnd	*new;

	printf("%s\n", (*list)->str);
	new = (t_cmnd *)malloc(sizeof(t_cmnd));
	new->label = find_label(list);
	if (!(new->command_name = find_command_name(list, new->label, a)))
	{
		free(new);
		return (NULL);
	}
	new->arg = find_args(list, new->label, new->command_name, a);
	printf("label:%s command:%d \n args:%d %d %s \n\t%d %d %s \n\t%d %d %s \n", new->label, new->command_name, new->arg.arg_arr[0].type, new->arg.arg_arr[0].value, new->arg.arg_arr[0].text, 
		new->arg.arg_arr[1].type, new->arg.arg_arr[1].value, new->arg.arg_arr[1].text,
		new->arg.arg_arr[2].type, new->arg.arg_arr[2].value, new->arg.arg_arr[2].text);
	// new->n_byte = count_bytes(new);
	new->next = NULL;
	return (new);
}

int		validation_commands(t_lst **list, t_asm *a)
{
	t_cmnd	*head;

	if (!(a->command = new_command(list, a)))
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
		if (!(head->next = new_command(list, a)))
		{
			ft_putendl("Wrong command");
			exit(0);
		}
		head = head->next;
		(*list) = (*list)->next;
	}
	return (1);
}
