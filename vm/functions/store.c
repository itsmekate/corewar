/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:01:57 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:01:59 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int 		initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	move = 2;
	if (arg[0] != REG_CODE || !arg[1] || arg[1] > IND_CODE || arg[1] == DIR_CODE || arg[2])
	{
		if (!arg[0])
		{
			log_move(corewar, process, move);
			move_process(move, process, corewar);
		}
		else
			error_codage(&arg[0], process, corewar);
		log_func(corewar, "store", 0);
		return (0);
	}
	return (move);
}

void			store(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	int 			status;


	// int i = -1;
	// while (++i < 16)
	// 	printf("%08x\n", process->reg[i]);
	if (!(move = initialize(&arg[0], corewar, process)))
	{
		log_func(corewar, "store", 0);
		return ;
	}
	// printf("reg %i\n", get_arg(1, process->position + move, corewar));
	status = get_value(&arg[0], process, corewar, &move);
	if (arg[1] == REG_CODE)
	{
		//printf("REG_CODE\n");
		if (get_value(&arg[1], process, corewar, &move) && status)
			process->reg[arg[2]] = arg[0];
	}
	else if (arg[1] == IND_CODE)
	{
		//printf("IND_CODE\n");
		// printf("%08x\n", arg[0]);
		arg[2] = get_arg(2, process->position + move, corewar);
		move += 2;
		// printf("%hi\n", (short)arg[2]);
		if (status)
			set_unsigned_int(arg[0], get_index(process->position + (short)arg[2] % IDX_MOD),
				corewar, process->player);
	}
	log_move(corewar, process, move);
	move_process(move, process, corewar);
	log_func(corewar, "store", 1);
}
