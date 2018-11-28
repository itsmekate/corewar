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

static void 	do_aff(t_corewar *corewar, unsigned int arg, t_process *process)
{
	char			str[2];
	char 			*msg;

	arg = process->reg[arg - 1] % 256;
	str[0] = arg;
	str[1] = '\0';
	if (corewar->verbal & L_FUNC)
	{
		msg = log_func(2, "aff: ", str);
		ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		free(msg);
	}
	else if (corewar->visual_mode && (corewar->verbal & L_AFF || !corewar->verbal))
		ft_lstadd(&corewar->log, ft_lstnew(str, 2));
	else if (corewar->verbal & L_AFF)
		ft_putstr_fd(str, 1);
}

void			aff(t_corewar *corewar, t_process *process)
{
	int				codage;
	unsigned int 	arg;

	codage = get_arg(1, process->position + 1, corewar);
	if (codage == 0x40)
	{
		arg = get_arg(1, process->position + 2, corewar);
		if (arg <= REG_NUMBER && arg)
			do_aff(corewar, arg, process);
		log_move(corewar, process, 3);
		move_process(3, process, corewar);
		return ;
	}
	log_move(corewar, process, 2);
	move_process(2, process, corewar);
}
