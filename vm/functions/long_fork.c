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

void			long_fork(t_corewar *corewar, t_process *process)
{
	short			arg1;
	t_process		*res;
	char			*log_process;

		//printf("long fork\n");
	arg1 = get_arg(2, process->position + 1, corewar);
	res = copy_process(process);
	ft_lstadd(&corewar->processes, obj_in_lst(res));
	move_process(arg1, res, corewar);
	//log
	log_process = ft_itoa_base(process->number, 10, 0);
	log_func(corewar, 2, "lfork copied process: ", log_process);
	free(log_process);
	//end log
	log_move(corewar, process, 3);
	move_process(3, process, corewar);
}
