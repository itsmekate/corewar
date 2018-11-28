/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:01:06 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:01:08 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void			log(t_corewar *corewar, int pr)
{
	char			*log_process;
	char			*msg;

	if (corewar->verbal & L_FUNC)
	{
		log_process = ft_itoa_base(pr, 10, 0);
		msg = log_func(2, "lfork copied process: ", log_process);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_process);
	}
}

void			long_fork(t_corewar *corewar, t_process *process)
{
	short			arg1;
	t_process		*res;

printf("long fork\n");
	arg1 = get_arg(2, process->position + 1, corewar);
	res = copy_process(process);
	ft_lstadd(&corewar->processes, obj_in_lst(res));
	move_process(arg1, res, corewar);
	//log
	log(corewar, res->number);
	//end log
	log_move(corewar, process, 3);
	move_process(3, process, corewar);
}
