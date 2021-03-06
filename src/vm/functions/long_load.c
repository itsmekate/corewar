/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:01:15 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:01:16 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void			get_value_long(unsigned int *arg, t_process *process,
	t_corewar *corewar, int *move)
{
	*arg = get_arg(2, process->position + *move, corewar);
	*move = *move + 2;
	*arg = get_arg(4, process->position + (short)*arg, corewar);
}

static int			initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int move;

	move = 2;
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(arg, process, corewar);
	if (arg[0] == REG_CODE || arg[0] > IND_CODE || arg[1] != REG_CODE || arg[2])
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	if (arg[0] == IND_CODE)
		get_value_long(&arg[0], process, corewar, &move);
	else
		get_value(&arg[0], process, corewar, &move);
	arg[1] = get_arg(1, process->position + move++, corewar);
	if (arg[1] > REG_NUMBER || !arg[1])
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	return (move);
}

static void			log(t_corewar *corewar, unsigned int res, int reg)
{
	char			*log_res;
	char			*log_reg;
	char			*msg;

	if (corewar->verbal & L_FUNC && corewar->start <= corewar->cycle)
	{
		log_res = ft_itoa_base(res, 16, 8);
		log_reg = ft_itoa(reg);
		msg = log_func(2, "lld result: 0x", log_res, " registry: ", log_reg);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_res);
		free(log_reg);
	}
}

void				long_load(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	process->reg[arg[1] - 1] = arg[0];
	if (!arg[0])
		process->carry = 1;
	else
		process->carry = 0;
	log(corewar, process->reg[arg[1] - 1], (int)arg[1]);
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
