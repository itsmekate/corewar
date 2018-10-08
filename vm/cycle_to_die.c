#include "vm.h"

static int		process_lives(t_corewar *corewar)
{
	int 	res;
	t_list	*lst;
	t_process *process;

	res = 0;
	lst = corewar->processes;
	while(lst)
	{
		process = lst->content;
		res += process->alive;
		lst = lst->next;
	}
	return (res);
}

static void 	players_lives(t_corewar *corewar)
{
	int			i;
	static int	n = 0;

	i = -1;
	if (process_lives(corewar) >= NBR_LIVE)
	{	
		n = 0;
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

void			cycle_to_die(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;

	// printf("cycle_to_die!! %i\n", corewar->cycle);
	// print_map(corewar);
	// printf("\n");
	// sleep(1);
	players_lives(corewar);
	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		if (!pr->alive)
		{
			// printf("kill\n");
			kill_process(corewar, pr);
			lst = corewar->processes;
		}
		else
		{
			//pr->alive = 0;
			lst = lst->next;
		}
	}
	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		pr->alive = 0;
		lst = lst->next;
	}
}