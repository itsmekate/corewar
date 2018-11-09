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
	int			index;
	char		*log_index;

	
	 //printf("zjump\n");
					
	if (!process->carry)
	{
		//printf("carry is absent\n");
		log_func(corewar, 1, "zjump FAIL");
		log_move(corewar, process, 3);
		move_process(3, process, corewar);
		return;
	}
	dir = get_arg(2, process->position + 1, corewar);
	index = dir % IDX_MOD;
	move_process(index, process, corewar);
	log_index = ft_itoa_base(index, 10, 0);
	log_func(corewar, 2, "zjump ", log_index);
	free(log_index);
	//sleep(2);
	//print_map(corewar);
	//sleep(4);

}
