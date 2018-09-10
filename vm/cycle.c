#include "vm.h"

static void		process_execute(t_process *process)
{
	(void)process;
}

static void		process_cycle(t_process *process)
{
	if (--process->cycle)
		return ;
	process_execute(process);
}

static void		nbr_live(t_corewar *corewar)
{
	static int	n = 0;
	int			i;

	i = -1;
	while (++i < corewar->players_num)
	{
		if (corewar->players[i]->process_num >= NBR_LIVE)
		{
			n = 0;
			corewar->cycle_to_die -= CYCLE_DELTA;
			return;
		}
	}
	n++;
	if (n >= MAX_CHECKS)
	{
		corewar->cycle_to_die -= CYCLE_DELTA;
		n = 0;
	}
}

static void		cycle_to_die(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		if (!pr->alive)
			kill_process(corewar, pr);
		else
			pr->alive = 0;
		lst = lst->next;
	}
	nbr_live(corewar);
}

void			grand_cycle(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	while (42)
	{
		if (++corewar->cycle && !(corewar->cycle % corewar->cycle_to_die))
			cycle_to_die(corewar);
		if (corewar->cycle_to_die <= 0 || !corewar->processes)
			return ;
		lst = corewar->processes;
		while (lst)
		{
			pr = lst->content;
			process_cycle(pr);
			lst = lst->next;
		}
		printf("%ji\n", corewar->cycle);
	}
}