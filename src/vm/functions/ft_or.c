/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:59:41 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 21:59:42 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int		initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int move;
	int status;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[0] || arg[0] > IND_CODE || !arg[1] ||
		arg[1] > IND_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return (0);
	}
	move = 2;
	status = get_value(&arg[0], process, corewar, &move);
	status = status & get_value(&arg[1], process, corewar, &move);
	arg[2] = get_arg(1, process->position + move, corewar);
	move++;
	if (arg[2] > REG_NUMBER || !arg[2] || !status)
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	return (move);
}

static void		log(t_corewar *corewar, unsigned int result)
{
	char			*log_res;
	char			*msg;

	if (corewar->verbal & L_FUNC)
	{
		log_res = ft_itoa_base(result, 8, 8);
		msg = log_func(2, "or result: 0x", log_res);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_res);
	}
}

void			ft_or(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	process->reg[arg[2] - 1] = arg[0] | arg[1];
	if (!process->reg[arg[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	log(corewar, process->reg[arg[2] - 1]);
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
