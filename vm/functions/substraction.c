/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substraction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:02:20 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:02:21 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void			substraction(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] != REG_CODE || arg[1] != REG_CODE || arg[2] != REG_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	arg[0] = get_arg(1, process->position + 2, corewar);
	arg[1] = get_arg(1, process->position + 3, corewar);
	arg[2] = get_arg(1, process->position + 4, corewar);
	if (arg[0] >= REG_NUMBER || arg[1] >= REG_NUMBER || arg[2] >= REG_NUMBER)
		return;
	arg[0] = process->reg[arg[0]];
	arg[1] = process->reg[arg[1]];
	process->reg[arg[2]] = arg[0] - arg[1];
	if (process->reg[arg[2]])
		process->carry = 0;
	else
		process->carry = 1;
	log_move(corewar, process, 5);
	move_process(5, process, corewar);
}
