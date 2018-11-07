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
			//corewar->players[i]->lives++;
			//corewar->lives_ok++;
			log_lives(corewar, corewar->players[i]);
		}
	}
}

void			live(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;
	char			*log_player;
	char			*log_process;

	//printf("live\n");
	process->alive++;
	corewar->lives_all++;
	dir = get_arg(4, process->position + 1, corewar);
	player_alive(dir, corewar);

	//log
	// log_player = ft_itoa_base((int)dir, 10, 0);
	// log_process = ft_itoa_base(process->number, 10, 0);
	// log_func(, "live ", "player: ", log_player, "process: ", log_process);
	// free(log_player);
	// free(log_process);
	//end log

	log_move(corewar, process, 5);
	move_process(5, process, corewar);
	//sleep(1);
}
