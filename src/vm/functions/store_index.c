/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_index.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:02:07 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:02:09 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static void		log(t_corewar *corewar, uintmax_t value, int addr)
{
	char		*log_res;
	char		*log_store;
	char		*msg;

	if (corewar->verbal & L_FUNC && corewar->start <= corewar->cycle)
	{
		log_res = ft_itoa_base((uintmax_t)value, 16, 8);
		log_store = ft_itoa(addr);
		msg = log_func(4, "sti value: 0x", log_res, " addr: ", log_store);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_res);
		free(log_store);
	}
}

void			store_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	int				status;
	int				place;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] != REG_CODE || !arg[1] || arg[1] > IND_CODE || !arg[2]
		|| arg[1] > DIR_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	status = get_value(&arg[0], process, corewar, &move);
	status = status & get_value(&arg[1], process, corewar, &move);
	status = status & get_value(&arg[2], process, corewar, &move);
	if (status)
	{
		place = process->position + ((short)arg[1] + (short)arg[2]) % IDX_MOD;
		set_unsigned_int(arg[0], get_index(place), corewar, process->player);
		log(corewar, (uintmax_t)arg[0], place - process->position);
	}
	log_move(corewar, process, move);
	move_process(move, process, corewar);
}
