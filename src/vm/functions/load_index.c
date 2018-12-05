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

static void		log(t_corewar *corewar, unsigned int res)
{
	char			*log_res;
	char			*msg;

	if (corewar->verbal & L_FUNC && corewar->start < corewar->cycle)
	{
		log_res = ft_itoa_base(res, 8, 8);
		msg = log_func(2, "ldi result: 0x", log_res);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_res);
	}
}

static void 	load_i(t_corewar *corewar, t_process *process,
	unsigned int arg2, unsigned int arg0)
{
	if (arg2 <= REG_NUMBER && arg2)
	{
		process->reg[arg2 - 1] = arg0;
		log(corewar, arg0);
	}
}

void			load_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	int				status;
	int				index;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] > IND_CODE || arg[1] > DIR_CODE || arg[2] > REG_CODE ||
		!arg[0] || !arg[1] || !arg[2])
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	status = get_value(&arg[0], process, corewar, &move);
	status = !status ? 0 : get_value(&arg[1], process, corewar, &move);
	if (status)
	{
		index = ((short)arg[0] + (short)arg[1]) % IDX_MOD;
		arg[0] = get_arg(4, process->position + index, corewar);
		arg[2] = get_arg(1, process->position + move, corewar);
		load_i(corewar, process, arg[2], arg[0]);
	}
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
}
