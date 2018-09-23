#include "vm.h"

t_process		*get_duplicate_process(t_process *process, t_corewar *corewar)
{
	static int			last_cycle = 0;
	static t_process	*last_pr = NULL;
	static t_list		*lst = NULL;
	t_process			*pr;

	if (last_cycle != corewar->cycle || last_pr != process)
	{
		last_cycle = corewar->cycle;
		last_pr = process;
		lst = corewar->processes;
	}
	while (lst)
	{
		pr = lst->content;
		lst = lst->next;
		if (pr->cycle == process->cycle && pr->position == 
			process->position && pr->command == process->command)
			return (pr);
	}
	return (NULL);
}