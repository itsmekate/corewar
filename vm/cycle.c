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
	int			k;

	i = -1;
	k = 0;
	printf("cycle_to_die %i, cycle %i\n", corewar->cycle_to_die, corewar->cycle);
	while (++i < corewar->players_num)
	{
		if (corewar->players[i]->process_num >= NBR_LIVE)
		{
			n = 0;
			k = 1;
		}
		printf("%i\n", corewar->players[i]->process_num);
		corewar->players[i]->process_num = 0;
		printf("%i\n", corewar->players[i]->process_num);

	}
	if (k)
	{
		corewar->cycle_to_die -= CYCLE_DELTA;
		log_cycle_to_die(corewar);
		return ;
	}
	n++;
	if (n >= MAX_CHECKS)
	{
		corewar->cycle_to_die -= CYCLE_DELTA;
		log_cycle_to_die(corewar);
		n = 0;
	}
}

static void		cycle_to_die(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	//printf("cycle_to_die!! %ju\n", corewar->cycle);
	// print_map(corewar);
	// printf("\n");
	// sleep(1);
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
		if (corewar->start <= ++corewar->cycle && corewar->visual_mode)
			visualize(corewar);
		log_cycle(corewar);
		if (!(corewar->cycle % corewar->cycle_to_die))
			cycle_to_die(corewar);
		if (corewar->cycle_to_die <= 0 || !corewar->processes || corewar->cycle < 0)
			return ;
		lst = corewar->processes;
		while (lst)
		{
			pr = lst->content;
			process_cycle(corewar, pr);
			lst = lst->next;
		}
		if ((int)corewar->cycle == corewar->dump)
		{
			//print_map(corewar);
			return ;
		}
	}
}