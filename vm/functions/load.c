/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:00:47 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:00:49 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"


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
		//error_codage(&arg[0], process, corewar);
		return (0);
	}
	get_value(&arg[0], process, corewar, &move);
	//printf("%08x\n", arg[0]);
	arg[1] = get_arg(1, process->position + move++, corewar);
	//printf("%i\n", arg[1]);
	if (arg[1] > REG_NUMBER || !arg[1])
	{
		log_move(corewar, process, move);
		move_process(move, process, corewar);
		return (0);
	}
	return (move);
}

static void		log(t_corewar *corewar, unsigned int res, int reg)
{
	char			*log_res;
	char			*log_reg;

	if (corewar->verbal & L_FUNC)
	{
		log_res = ft_itoa_base(res, 16, 8);
		log_reg = ft_itoa_base(reg, 10, 0);
		log_func(corewar , 4, "ld result: 0x", log_res, " registry: ", log_reg);
		free(log_res);
		free(log_reg);
	}
}

void				load(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int 			move;

	// int i = -1;
	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	//printf("\n\n");
	//printf("load \n");
	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	//printf("%i\n", arg[1]);
	//printf(" inited \n");
	//printf("%u\n", arg[1]);
	// if (process->number == 24)
	// {
	// 	printf("%i\n", arg[2]);
	// 	sleep (3);
	// }
	process->reg[arg[1] - 1] = arg[0];
	if (!arg[0])
		process->carry = 1;
	else
		process->carry = 0;
	//printf(" made \n");

	//log
	log(corewar, process->reg[arg[1] - 1], arg[1]);
	//end log

	log_move(corewar, process, move);
	move_process(move, process, corewar);
	//printf(" moved \n");
	//printf(" logged f \n");
	// i = -1;
	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	// printf("\n\n");
}
