/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:59:48 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 21:59:49 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int		initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[0] || arg[0] > IND_CODE || !arg[1] ||
		arg[1] > IND_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return (0);
	}
	move = 2;
	get_value(&arg[0], process, corewar, &move);
	get_value(&arg[1], process, corewar, &move);
	arg[2] = get_arg(1, process->position + move, corewar);
	move++;
	if (arg[2] > REG_NUMBER)
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	return (move);
}

void			ft_xor(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	process->reg[arg[2] - 1] = arg[0] ^ arg[1];
	if (!process->reg[arg[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
