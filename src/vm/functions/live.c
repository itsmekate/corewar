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

static void 	log_alive(t_corewar *corewar, t_player *player)
{
	char	*number;
	char 	*msg;

	if (corewar->verbal & L_LIVE && corewar->cycle > corewar->start)
	{
		number = ft_itoa(player->number);
		msg = log_func(5, "Player ", number, " (", player->name, ") is said to be alive");
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl_fd(msg, 1);
		free(number);
		free(msg);
	}
}

static void		player_alive(unsigned int number, t_corewar *corewar)
{
	int		i;

	i = -1;
	while (++i < corewar->players_num)
	{
		if (0xffffffff - corewar->players[i]->number + 1 == number)
		{
			corewar->players[i]->process_num++;
			corewar->last_alive = corewar->players[i]->number;
			log_alive(corewar, corewar->players[i]);
			return ;
		}
	}
}

static void		log(t_corewar *corewar, int player, int process)
{
	char			*log_player;
	char			*log_process;
	char			*msg;

	if (corewar->verbal & L_FUNC && corewar->cycle > corewar->start)
	{
		log_player = ft_itoa(player);
		log_process = ft_itoa_base(process, 10, 0);
		msg = log_func(5, "live ", "player: ",
			log_player, " process: ", log_process);
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

	process->alive++;
	corewar->lives_all++;
	dir = get_arg(4, process->position + 1, corewar);
	player_alive(dir, corewar);
	log(corewar, dir, process->number);
	log_move(corewar, process, 5);
	move_process(5, process, corewar);
}
