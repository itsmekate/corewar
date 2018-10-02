#include "vm.h"

static void		process_cycle(t_corewar *corewar, t_process *process)
{
	void			(*f) (t_corewar *, t_process *);

// int i = -1;
// 	while (++i < 16)
// 	{
// 		printf("%08x\n", process->reg[i]);
// 	}
// 	printf("\n\n");
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
	


	//printf("%i\n", process->carry);
	// print_map(corewar);
	// sleep(1);
}

void			grand_cycle(t_corewar *corewar)
{
	t_list		*lst;
	t_process	*pr;
	int			ctd;

	ctd = 0;
	while (42)
	{
		if (!corewar->processes)
		{
			print_winner(get_winner(corewar));
			return ;
		}
		if (corewar->start <= ++corewar->cycle && corewar->visual_mode)
			visualize(corewar);
		log_cycle(corewar);
		lst = corewar->processes;
		//printf("going to process cycle\n");
		while (lst)
		{
			pr = lst->content;
			process_cycle(corewar, pr);
			lst = lst->next;
		}
		
		if (corewar->cycle_to_die <= 0 || !corewar->processes || corewar->cycle < 0)
		{
			print_winner(get_winner(corewar));
			return ;
		}
		if ((int)corewar->cycle == corewar->dump)
		{
			dump_map(corewar);
			return ;
		}
		if (++ctd >= corewar->cycle_to_die)
		{
			cycle_to_die(corewar);
			ctd = 0;
		}
		//printf("end cycle\n");
	}
}