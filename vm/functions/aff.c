/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:59:01 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 21:59:03 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void			aff(t_corewar *corewar, t_process *process)
{
	int				codage;
	unsigned int 	arg;
	char			str[2];

//printf("aff\n");
	codage = get_arg(1, process->position + 1, corewar);
	if (codage == 0x40)
	{
		arg = get_arg(1, process->position + 2, corewar);
		if (arg <= REG_NUMBER)
		{
			arg = process->reg[arg - 1] % 256;
			str[0] = arg;
			str[1] = '\0';
			if (corewar->verbal)
				log_func(corewar, 2, "aff argument value: ", str);
			else
				ft_putstr_fd(str, 1);
		}
		log_move(corewar, process, 3);
		move_process(3, process, corewar);
		return ;
	}
	log_move(corewar, process, 2);
	move_process(2, process, corewar);
}
