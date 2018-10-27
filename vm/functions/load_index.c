/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:00:55 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:00:57 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void			load_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	int 			status;
	int buf;

	//printf("load_index\n");
	// int i = -1;

	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] > IND_CODE || arg[1] > DIR_CODE || arg[2] > REG_CODE ||
		!arg[0] || !arg[1] || !arg[2])
	{
		error_codage(&arg[0], process, corewar);
		log_func(corewar, "load_index", 0);
		return ;
	}
	buf = arg[1];
	move = 2;
	status = get_value(&arg[0], process, corewar, &move);
	status = !status ? 0 : get_value(&arg[1], process, corewar, &move);
	//printf("arg1 %i\n", arg[1]);
	if (status)
	{
		int index = (short)(arg[0] + arg[1]) % IDX_MOD;
		if (buf == REG_CODE && (int)arg[1] > 0)
			index = ((short)arg[0] + (int)arg[1]) % IDX_MOD;
		//printf("index %i\n", index + process->position);
		arg[0] = get_arg(4, process->position + index, corewar);

		arg[2] = get_arg(1, process->position + move, corewar);
	// 	if (process->number == 24)
	// {
	// 	//printf("%i\n", arg[2]);
	// 	sleep (3);
	// }
		if (arg[2] <= REG_NUMBER)
			process->reg[arg[2] - 1] = arg[0];
		// else
		// 	printf("ni!\n");
	}
	// i = -1;

	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	// printf("registry %i, value %08x\n", arg[2], arg[0]);
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
	log_func(corewar, "load_index", 1);
}
