/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:00:41 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:00:42 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

void			player_alive(unsigned int number, t_corewar *corewar)
{
	int		i;

	i = -1;
	//printf("number %u\n", number);
	while (++i < corewar->players_num)
	{
		if (0xffffffff - corewar->players[i]->number + 1 == number)
		{
			//printf("alive\n");
			corewar->players[i]->process_num++;
			corewar->last_alive = corewar->players[i]->number;
			log_lives(corewar, corewar->players[i]);
		}
	}
}

void			live(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;

	//printf("live\n");
	process->alive++;
	dir = get_arg(4, process->position + 1, corewar);
	player_alive(dir, corewar);
	log_move(corewar, process, 5);
	move_process(5, process, corewar);
	//sleep(1);
}
