/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjump.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:02:34 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:02:36 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void		log(t_corewar *corewar, int index)
{
	char		*log_index;
	char		*msg;

	if (corewar->verbal & L_FUNC && corewar->start < corewar->cycle)
	{
		log_index = ft_itoa(index);
		msg = log_func(2, "zjump ", log_index);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_index);
	}
}

void			zjump(t_corewar *corewar, t_process *process)
{
	short		dir;
	int			index;

	if (!process->carry)
	{
		if (corewar->verbal & L_FUNC)
		{
			if (corewar->visual_mode)
				ft_lstadd(&corewar->log, ft_lstnew("zjump FAILED", 13));
			else
				ft_putendl_fd("zjump FAILED", 1);
		}
		log_move(corewar, process, 3);
		move_process(3, process, corewar);
		return ;
	}
	dir = get_arg(2, process->position + 1, corewar);
	index = dir % IDX_MOD;
	move_process(index, process, corewar);
	log(corewar, index);
}
