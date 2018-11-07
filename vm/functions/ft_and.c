/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:59:17 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 21:59:18 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int		initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int move;
	int status;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[0] || arg[0] > IND_CODE || !arg[1] ||
		arg[1] > IND_CODE)
	{
		error_codage(&arg[0], process, corewar);
		log_func(corewar, "ft_and", 0);
		return (0);
	}
	move = 2;
	status = get_value(&arg[0], process, corewar, &move);
	status = status & get_value(&arg[1], process, corewar, &move);
	arg[2] = get_arg(1, process->position + move, corewar);
	move++;
	if (arg[2] > REG_NUMBER || !arg[2] || !status)
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	return (move);
}

void			ft_and(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	char			*log_res;

//printf("and\n");
	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	process->reg[arg[2] - 1] = arg[0] & arg[1];
	if (!process->reg[arg[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;

	//log
	// log_res = ft_itoa_base(arg[3], 8, 8);
	// log_func(2, "and ", log_res);
	// free(log_res);
	//end log
	
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
