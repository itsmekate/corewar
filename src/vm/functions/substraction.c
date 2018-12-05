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

static int		initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(arg, process, corewar);
	if (arg[0] != REG_CODE || arg[1] != REG_CODE || arg[2] != REG_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return (0);
	}
	arg[0] = get_arg(1, process->position + 2, corewar);
	arg[1] = get_arg(1, process->position + 3, corewar);
	arg[2] = get_arg(1, process->position + 4, corewar);
	if (arg[0] > REG_NUMBER || arg[1] > REG_NUMBER || arg[2] > REG_NUMBER
			|| !arg[0] || !arg[1] || !arg[2])
	{
		log_move(corewar, process, 5);
		move_process(5, process, corewar);
		return (0);
	}
	return (5);
}

static void		log(t_corewar *corewar, unsigned int result)
{
	char			*log_res;
	char			*msg;

	if (corewar->verbal & L_FUNC && corewar->start < corewar->cycle)
	{
		log_res = ft_itoa_base(result, 8, 8);
		msg = log_func(2, "sub result: 0x", log_res);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_res);
	}
}

void			substraction(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	arg[0] = process->reg[arg[0] - 1];
	arg[1] = process->reg[arg[1] - 1];
	process->reg[arg[2] - 1] = arg[0] - arg[1];
	if (process->reg[arg[2] - 1])
		process->carry = 0;
	else
		process->carry = 1;
	log(corewar, process->reg[arg[2] - 1]);
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
