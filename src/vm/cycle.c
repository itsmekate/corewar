#include "vm.h"

static void		process(t_corewar *corewar, t_process *process)
{
	void			(*f) (t_corewar *, t_process *);

	if (--process->cycle)
		return ;
	if (process->command < 1 || process->command > 16)
	{
		move_process(1, process, corewar);
		return ;
	}
	f = corewar->f[(process->command & 0xff) - 1];
	f(corewar, process);
	if (corewar->visual_mode && corewar->debug)
		corewar->pause = 1;
	if (corewar->start <= corewar->cycle && corewar->visual_mode)
		visualize(corewar);
}

static void		process_cycle(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	if (corewar->start <= corewar->cycle && corewar->visual_mode && !corewar->cycle)
		visualize(corewar);
	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		process(corewar, pr);
		lst = lst->next;
	}
	if (corewar->start == corewar->cycle && corewar->visual_mode)
		visualize(corewar);
}

static void		game_over(t_corewar *corewar)
{
	if (corewar->visual_mode)
	{
		corewar->pause = 2;
		visualize(corewar);
	}
	else
		print_winner(get_winner(corewar));
}

void			grand_cycle(t_corewar *corewar)
{
	int			ctd;

	ctd = 0;
	while (42)
	{
		if (corewar->cycle_to_die <= 0 || !corewar->processes ||
			corewar->cycle < 0)
		{
			game_over(corewar);
			return ;
		}
		corewar->cycle++;
		log_cycle(corewar);
		process_cycle(corewar);
		if (corewar->cycle == corewar->dump && !corewar->visual_mode)
		{
			dump_map(corewar);
			return ;
		}
		if (++ctd >= corewar->cycle_to_die)
		{
			cycle_to_die(corewar);
			ctd = 0;
		}
	}
}
