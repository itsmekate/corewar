/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_load_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:01:39 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:01:41 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int		initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int 		move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[1] || arg[1] > DIR_CODE ||
		!arg[0] || arg[0] > IND_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return (0);
	}
	move = 2;
	if (!get_value(&arg[0], process, corewar, &move) || 
		!get_value(&arg[1], process, corewar, &move) ||
		(arg[2] = get_arg(1, process->position + move++, corewar)) >= REG_NUMBER)
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	return (move);
}

void			long_load_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	arg[0] = get_arg(4, process->position + (short)arg[0] +
		(short)arg[1], corewar);
	process->reg[arg[2]] = arg[0];
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
