/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_to_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:58:40 by dzabrots          #+#    #+#             */
/*   Updated: 2018/12/06 15:58:42 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		players_lives(t_corewar *corewar)
{
	static int	n = 0;

	n++;
	if (corewar->lives_all >= NBR_LIVE)
	{
		n = 0;
		corewar->cycle_to_die -= CYCLE_DELTA;
		log_cycle_to_die(corewar);
		return ;
	}
	if (n >= MAX_CHECKS)
	{
		corewar->cycle_to_die -= CYCLE_DELTA;
		log_cycle_to_die(corewar);
		n = 0;
	}
}

static void		log(t_corewar *corewar, t_process *pr)
{
	char *msg;
	char *pr_num;

	if (corewar->verbal & L_DEATH && corewar->cycle > corewar->start)
	{
		pr_num = ft_itoa(pr->number);
		msg = ft_strjoin("kill process ", pr_num);
		free(pr_num);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(msg, ft_strlen(msg) + 1));
		else
			ft_putendl(msg);
		free(msg);
	}
}

static void		clear_alives(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		pr->alive = 0;
		lst = lst->next;
	}
}

void			cycle_to_die(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	players_lives(corewar);
	corewar->lives_all = 0;
	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		if (!pr->alive)
		{
			log(corewar, pr);
			kill_process(corewar, pr);
			if (corewar->start <= corewar->cycle && corewar->visual_mode)
				visualize(corewar);
			lst = corewar->processes;
		}
		else
			lst = lst->next;
	}
	clear_alives(corewar);
}
