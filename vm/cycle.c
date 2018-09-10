#include "vm.h"

static void		proccess_execute(t_procces *procces)
{
	(void)procces;
}

static void		process_cycle(t_procces *procces)
{
	if (--procces->cycle)
		return ;
	proccess_execute(procces);
}

static void		nbr_live(t_corewar *corewar)
{
	static int	n = 0;
	int			i;

	i = -1;
	while (++i < corewar->players_num)
	{
		if (corewar->players[i]->players_num >= NBR_LIVE)
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

	lst = corewar->procceses;
	while (lst)
	{
		pr = lst->content;
		if (!pr->alive)
			kill_process(corewar, procces);
		else
			pr->alive = 0;
		lst = lst->next;
	}
	nbr_live(corewar);
}

void			grand_cycle(t_corewar *corewar)
{
	while (42)
	{
		if (++corewar->cycle && !(corewar->cycle % corewar->cycle_to_die))
			cycle_to_die(t_corewar *corewar);
		if (corewar->cycle_to_die <= 0 || !corewar->procceses)
			return ;

	}
}