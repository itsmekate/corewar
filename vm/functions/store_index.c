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

static void		log(t_corewar *corewar)
{
	char		*msg;

	if (corewar->verbal & L_FUNC)
	{
		msg = log_func(1, "sti");
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
	}
}

void			store_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	// short 			index;
	int 			status;
	int				buf;
	// char			*log_res;
	// char			*log_store;

	// int i = -1;

	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	// printf("store_index\n");
	//print_map(corewar);
	//printf("%i\n", process->number);
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] != REG_CODE || !arg[1] || arg[1] > IND_CODE || !arg[2]
		|| arg[1] > DIR_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	buf = arg[2];
	move = 2;
	status = get_value(&arg[0], process, corewar, &move);
	// printf("value is %08x\n", arg[0]);
	status = status & get_value(&arg[1], process, corewar, &move);
	// printf("sec arg %hi\n", (short)arg[1]);

	status = status & get_value(&arg[2], process, corewar, &move);
	//printf("thd arg %i\n", arg[2]);
	//printf("%i\n", status);
	if (status)
	{
	//printf("thrd arg %hi\n", (short)arg[2]);
	// if (error_arg(process, corewar, move))
	// 	return ;
	//printf("1 = %hhi, 2 = %hhi\n", (char)arg[1], (char)arg[2]);
	//printf("1 = %hi, 2 = %hi\n", (short)arg[1], (short)arg[2]);
	//printf("1 = %u, 2 = %u\n", arg[1], arg[2]);
			// index = arg[1] + arg[2];
			// printf("index = %i\n", index % IDX_MOD);
			int place = process->position + (short)arg[1] % IDX_MOD + (short)arg[2] % IDX_MOD;
			if (buf == REG_CODE && (int)arg[2] > 0)
			{
			//	 printf("reg\n");
				place = process->position + ((short)arg[1] + (int)arg[2]) % IDX_MOD;
			}
			// int real_place = process->position + index % IDX_MOD;
			//printf("place %i\n", place);
			// if (place != real_place)
			// {
			// 	printf(" cycle %i\n", corewar->cycle);
			// 	sleep (3);
			// }
	//printf("%hhi; %i\n", (char)index, (char )index % IDX_MOD);
	
		// if (index)
			// printf("%08x\n", arg[0]);
			// if (arg[0] == 0x64)
			set_unsigned_int(arg[0], get_index(place), corewar, process->player);
			
			//log
			log(corewar);

			// log_res = ft_itoa_base((int)arg[0], 16, 8);
			// printf("log_res : %s\n", log_res);

			// printf("place : %i\n", place - process->position);
			
			// log_store = my_itoa(place - process->position);
			// printf("log_store : %s\n", log_store);

			// log_func(corewar, 4, "store ", log_res, " addr: ", log_store);

			// free(log_res);
			// free(log_store);
			
			//log end

	// if (arg2 == DIR_CODE && arg3 == DIR_CODE)
	//  	reg_dir_dir(arg1, corewar, process);
	 // else
			// sleep(3);
	//  	printf("I DONT KNOW WHAT TO DO!!!!\n");
	
	}
	log_move(corewar, process, move);
	move_process(move, process, corewar);
	//sleep(3);
}
