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

// static unsigned int		dir_load(t_corewar *corewar, t_process *process)
// {
// 	unsigned int	dir;
// 	int				reg;

// 	dir = get_arg(4, process->position + 2, corewar);
// 	reg = get_arg(1, process->position + 6, corewar);
// 	if (reg >= 0 && reg < REG_NUMBER)
// 		process->reg[reg] = dir;
// 	// printf("registry %i, value %08x\n", reg, dir);

// 	log_move(corewar, process, 7);
// 	move_process(7, process, corewar);
// 	return (dir);
// }

// static unsigned int		ind_load(t_corewar *corewar, t_process *process)
// {
// 	unsigned int	dir;
// 	short			ind;
// 	int				reg;

// 	ind = get_arg(2, process->position + 2, corewar);
// 	dir = get_arg(4, process->position + ind % IDX_MOD, corewar);
// 	reg = get_arg(1, process->position + 4, corewar);
// 	if (reg >= 0 && reg < REG_NUMBER)
// 		process->reg[reg] = dir;
// 	// printf("registry %i, value %08x\n", reg, dir);
// 	log_move(corewar, process, 5);
// 	move_process(5, process, corewar);
// 	return (dir);
// }

// void					load(t_corewar *corewar, t_process *process)
// {
// 	char			codage;
// 	unsigned int	load;

// 	// printf("load\n");
// 	codage = get_arg(1, process->position + 1, corewar);
// 	load = 0;
// 	if (((codage & 0xff) >> 6) == DIR_CODE)
// 		load = dir_load(corewar, process);
// 	else if (((codage & 0xff) >> 6) == IND_CODE)
// 		load = ind_load(corewar, process);
// 	else
// 	{
// 		log_move(corewar, process, 2);
// 		move_process(2, process, corewar);
// 		return ;
// 	}
// 	if (!load)
// 		process->carry = 1;
// 	else
// 		process->carry = 0;
// }
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
		log_func(corewar, "load", 0);
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
		log_func(corewar, "load", 0);
		return (0);
	}
	return (move);
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
	// printf(" load \n");
	if (!(move = initialize(&arg[0], corewar, process)))
		return ;
	//printf("%i\n", arg[1]);
	//printf(" inited \n");
	//printf("%u\n", arg[1]);
	if (process->number == 24)
	{
		printf("%i\n", arg[2]);
		sleep (3);
	}
	process->reg[arg[1] - 1] = arg[0];
	if (!arg[0])
		process->carry = 1;
	else
		process->carry = 0;
	//printf(" made \n");
	log_move(corewar, process, move);
	move_process(move, process, corewar);
	//printf(" moved \n");
	log_func(corewar, "load", 1);
	//printf(" logged f \n");
	// i = -1;
	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	// printf("\n\n");
}

