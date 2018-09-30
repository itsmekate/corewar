#include "vm.h"

static int		process_lives(t_corewar *corewar, t_player *player)
{
	int 	res;
	t_list	*lst;
	t_process *process;

	res = 0;
	lst = corewar->processes;
	while(lst)
	{
		process = lst->content;
		if (process->player == player)
		{
			//printf("*%i\n", process->alive);
			res += process->alive;
		}
		lst = lst->next;
	}
	return (res);
}

static void 	players_lives(t_corewar *corewar)
{
	int			i;
	t_player	*player;
	static int	n = 0;
	int			k;

	k = 0;
	i = -1;
	while (++i < corewar->players_num)
	{
		player = corewar->players[i];
		if (process_lives(corewar, player) >= NBR_LIVE)
		{
			n = 0;
			k = 1;
		}
	}
	if (k)
	{
		corewar->cycle_to_die -= CYCLE_DELTA;
		log_cycle_to_die(corewar);
		return ;
	}
	n++;
	//printf("checks %i\n", n);
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

	//printf("cycle_to_die!! %i\n", corewar->cycle);
	// print_map(corewar);
	// printf("\n");
	// sleep(1);
	players_lives(corewar);
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
}