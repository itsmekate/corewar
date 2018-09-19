#include "vm.h"

static void		process_cycle(t_corewar *corewar, t_process *process)
{
	void			(*f) (t_corewar *, t_process *);

	if (--process->cycle)
		return ;
	//printf("position = %i, command = %02x\n", get_index(process->position), process->command & 0xff);
	if (process->command < 1 || process->command > 16)
	{
		//printf("oops\n");
		move_process(1, process, corewar);
		return ;
	}
	f = corewar->f[(process->command & 0xff) - 1];
	f(corewar, process);
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

	printf("cycle_to_die!! %ju\n", corewar->cycle);

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
			process_cycle(corewar, pr);
			lst = lst->next;
		}
		//visualize(corewar);
		//printf("%ju\n", corewar->cycle);
	}
}