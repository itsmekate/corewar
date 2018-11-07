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

void			ft_fork(t_corewar *corewar, t_process *process)
{
	short			arg1;
	t_process	*res;
	char		*log_res;
	char		*log_process_num;

	//printf("ft_fork\n");
	//print_map(corewar);
	//exit(0);
	arg1 = get_arg(2, process->position + 1, corewar);
	res = copy_process(process);
	ft_lstadd(&corewar->processes, obj_in_lst(res));
	move_process(arg1 % IDX_MOD, res, corewar);

	//log
	// log_res = ft_itoa_base(arg1 / IDX_MOD, 10, 0);
	// log_process_num = ft_itoa_base(res->number);
	// log_func(4, "fork ", log_res, " new procces: ", log_process_num);
	// free(log_res);
	// free(log_process_num);
	//end log

	log_move(corewar, process, 3);
	move_process(3, process, corewar);
	//print_map(corewar);
	//sleep(2);
	// if (!res->command)
	//exit(0);
}
