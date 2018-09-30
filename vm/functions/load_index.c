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

	// printf("load_index\n");
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] > IND_CODE || arg[1] > DIR_CODE || arg[2] > REG_CODE ||
		!arg[0] || !arg[1] || !arg[2])
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	get_value(&arg[0], process, corewar, &move);
	get_value(&arg[1], process, corewar, &move);
	arg[0] = get_arg(4, process->position + (short)((short)arg[0] +
		(short)arg[1]) % IDX_MOD, corewar);
	arg[2] = get_arg(1, process->position + move, corewar);
	if (arg[2] < REG_NUMBER)
		process->reg[arg[2]] = arg[0];
	// printf("registry %i, value %08x\n", arg[2], arg[0]);
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
}
