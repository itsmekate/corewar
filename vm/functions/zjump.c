/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjump.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:02:34 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:02:36 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void			zjump(t_corewar *corewar, t_process *process)
{
	short		dir;

	
	 //printf("zjump\n");
					
	if (!process->carry)
	{
		//printf("carry is absent\n");
		log_move(corewar, process, 3);
		move_process(3, process, corewar);
		log_func(corewar, "zjump", 0);
		return;
	}
	dir = get_arg(2, process->position + 1, corewar);
	move_process(dir % IDX_MOD, process, corewar);
	log_func(corewar, "zjump", 1);
	//sleep(2);
	//print_map(corewar);
	//sleep(4);

}
