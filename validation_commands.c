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
	new->n_byte = count_bytes(new, a);
	new->next = NULL;
	printf("bytes: %d\n", new->n_byte);
	return (new);
}

int			find_label_num(char *str, t_cmnd *cmnds)
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

int			label_to_numbers(t_cmnd	*cmnds)
{
	t_cmnd	*tmp;
	int		i;
	int		res;
	int		tmp_res;

	i = 0;
	res = 0;
	tmp = cmnds;
	while (cmnds)
	{
		i = 0;
		while (cmnds->arg.arg_arr[i].type && i < 3)
		{
			if (cmnds->arg.arg_arr[i].text)
			{
				if ((tmp_res = find_label_num(cmnds->arg.arg_arr[i].text, tmp)) == -1)
				{
					ft_strdel(&cmnds->arg.arg_arr[i].text);
					return (0);
				}
				cmnds->arg.arg_arr[i].value = tmp_res - res;
				ft_strdel(&cmnds->arg.arg_arr[i].text);
			}
			i++;
		}
		res += cmnds->n_byte;
		cmnds = cmnds->next;
	}
	return (1);
}

void		print_cmnds(t_cmnd	*new)
{
	printf("____________________________\n\n %s \n____________________________\n\n", "NEW COMMANDS LIST");
	while (new)
	{
		printf("label:%s command:%d \n args:%d %d %s \n\t%d %d %s \n\t%d %d %s \n", new->label, new->command_name, new->arg.arg_arr[0].type, new->arg.arg_arr[0].value, new->arg.arg_arr[0].text, 
		new->arg.arg_arr[1].type, new->arg.arg_arr[1].value, new->arg.arg_arr[1].text,
		new->arg.arg_arr[2].type, new->arg.arg_arr[2].value, new->arg.arg_arr[2].text);
		new = new->next;
	}
}

int			validation_commands(t_lst **list, t_asm *a)
{
	t_cmnd	*head;
	t_cmnd	*head_tmp;

	if (!(a->command = new_command(list, a)))
	{
		ft_putendl("Wrong command");
		exit(0);
	}
	head = a->command;
	head_tmp = head;
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
	if (!label_to_numbers(head_tmp))
	{
		ft_putendl("Wrong label args");
		return (0);
	}
	print_cmnds(head_tmp);
	return (1);
}
