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
			//log_lives(corewar, corewar->players[i]);
		}
	}
}

static void		log(t_corewar *corewar, int player, int process)
{
	char			*log_player;
	char			*log_process;
	char			*msg;

	if (corewar->verbal & L_FUNC)
	{
		log_player = ft_itoa(player);
		log_process = ft_itoa_base(process, 10, 0);
		msg = log_func(5, "live ", "player: ", log_player, " process: ", log_process);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(msg);
		free(log_player);
		free(log_process);
	}
}

void			live(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;

	//printf("live\n");
	process->alive++;
	corewar->lives_all++;
	dir = get_arg(4, process->position + 1, corewar);
	player_alive(dir, corewar);

	//log
	log(corewar, dir, process->number);
	//end log

	log_move(corewar, process, 5);
	move_process(5, process, corewar);
	//sleep(1);
}
