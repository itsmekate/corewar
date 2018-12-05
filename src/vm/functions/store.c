/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:01:57 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:01:59 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

static int			initialize(unsigned int *arg, t_corewar *corewar,
	t_process *process)
{
	int move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	move = 2;
	if (arg[0] != REG_CODE || !arg[1] ||
		arg[1] > IND_CODE || arg[1] == DIR_CODE || arg[2])
	{
		if (!arg[0])
		{
			log_move(corewar, process, move);
			move_process(move, process, corewar);
		}
		else
			error_codage(&arg[0], process, corewar);
		return (0);
	}
	return (move);
}

static void			log_2(t_corewar *corewar, char *log_res, char *log_store)
{
	char *msg;

	msg = log_func(4, "st result: 0x", log_res, " place: ", log_store);
	if (corewar->visual_mode)
		ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
	else
		ft_putendl_fd(msg, 1);
	free(msg);
}

static void			log(t_corewar *corewar, int code, unsigned int res, int reg)
{
	char			*log_res;
	char			*log_store;
	char			*msg;

	if (corewar->verbal & L_FUNC)
	{
		log_res = ft_itoa_base(res, 16, 8);
		log_store = ft_itoa(reg);
		if (code == REG_CODE)
		{
			msg = log_func(4, "st result: 0x",
				log_res, " registry: ", log_store);
			if (corewar->visual_mode)
				ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
			else
				ft_putendl_fd(msg, 1);
			free(msg);
		}
		else if (code == IND_CODE)
			log_2(corewar, log_res, log_store);
		free(log_res);
		free(log_store);
	}
}

static void			store_ind(t_corewar *corewar, t_process *process,
	unsigned int arg2, unsigned int arg0)
{
	set_unsigned_int(arg0, get_index(process->position +
				(short)arg2 % IDX_MOD), corewar, process->player);
	log(corewar, IND_CODE, arg0, (short)arg2 % IDX_MOD);
}

void				store(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	int				status;

	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	status = get_value(&arg[0], process, corewar, &move);
	if (arg[1] == REG_CODE)
	{
		arg[1] = get_arg(1, process->position + move, corewar);
		if (status && arg[1] && arg[1] <= REG_NUMBER)
		{
			process->reg[arg[1] - 1] = arg[0];
			log(corewar, REG_CODE, arg[0], arg[1]);
		}
	}
	else if (arg[1] == IND_CODE)
	{
		arg[2] = get_arg(2, process->position + move++, corewar);
		if (status)
			store_ind(corewar, process, arg[2], arg[0]);
	}
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
}
