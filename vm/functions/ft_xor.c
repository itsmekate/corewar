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

void			ft_xor(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[0] || arg[0] > IND_CODE || !arg[1] || arg[1] > IND_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	arg[0] = get_value(arg[0], process, corewar, &move);
	arg[1] = get_value(arg[1], process, corewar, &move);
	arg[2] = get_arg(1, process->position + move, corewar);
	if (arg[2] < REG_NUMBER)
		process->reg[arg[2]] = arg[0] ^ arg[1];
	{
		log_move(corewar, process, move + 1);
		move_process(move + 1, process, corewar);
		return ;
	}
	if (!process->reg[arg[2]])
		process->carry = 1;
	else
		process->carry = 0;
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
}
