#include "vm.h"

// static int		process_lives(t_corewar *corewar, t_player *player)
// {
// 	int 	res;
// 	t_list	*lst;
// 	t_process *process;

// 	//printf("lives = %i\n", player->lives);
// 	//player->lives = 0;
// 	res = 0;
// 	lst = corewar->processes;
// 	while(lst)
// 	{
// 		process = lst->content;
// 		if (process->player == player)
// 			res += process->alive;
// 		lst = lst->next;
// 	}
// 	printf("%i\n", res);
// 	return (res);
// }

static void 	players_lives(t_corewar *corewar)
{
	//int res;
	//int i;
	static int	n = 0;

	//i = -1;
	n++;
	//while (++i < corewar->players_num)
	//{
		//res = process_lives(corewar, corewar->players[i]);
		if (corewar->lives_all >= NBR_LIVE)
		{	
			n = 0;
			corewar->cycle_to_die -= CYCLE_DELTA;
			log_cycle_to_die(corewar);
			return ;
		}
	//}
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


	players_lives(corewar);
	//printf("ok = %i; all = %i; ctd = %i\n", corewar->lives_ok, corewar->lives_all, corewar->cycle_to_die);
	//corewar->lives_ok = 0;
	corewar->lives_all = 0;
	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		if (!pr->alive)
		{
			//printf("kill\n");
			kill_process(corewar, pr);
			lst = corewar->processes;
		}
		else
			lst = lst->next;
	}
	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		pr->alive = 0;
		lst = lst->next;
	}
}