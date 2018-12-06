/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:59:26 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 21:59:29 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

t_process		*copy_process(t_process *process)
{
	t_process	*res;
	int			i;

	if ((res = new_procces()))
	{
		res->position = process->position;
		res->player = process->player;
		res->alive = process->alive;
		res->carry = process->carry;
		i = -1;
		while (++i < REG_NUMBER)
			res->reg[i] = process->reg[i];
	}
	return (res);
}

static void		log(t_corewar *corewar, short res, int pr_num)
{
	char		*log_res;
	char		*log_process_num;
	char		*msg;

	if (corewar->verbal & L_FUNC && corewar->start <= corewar->cycle)
	{
		log_res = ft_itoa(res);
		log_process_num = ft_itoa(pr_num);
		msg = log_func(4, "fork ", log_res, " new procces: ", log_process_num);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_res);
		free(log_process_num);
	}
}

void			ft_fork(t_corewar *corewar, t_process *process)
{
	short		arg1;
	t_process	*res;

	arg1 = get_arg(2, process->position + 1, corewar);
	res = copy_process(process);
	ft_lstadd(&corewar->processes, obj_in_lst(res));
	move_process(arg1 % IDX_MOD, res, corewar);
	log(corewar, arg1 % IDX_MOD, res->number);
	log_move(corewar, process, 3);
	move_process(3, process, corewar);
}
