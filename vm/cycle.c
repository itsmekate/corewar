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

static void		cycle_to_die(t_corewar *corewar)
{
	static int	n = 0;
	t_list		*lst;
	t_process	*pr;

	lst = corewar->procceses;
	while(lst)
	{
		pr = lst
		lst = lst->next;
	}
}

void			grand_cycle(t_corewar *corewar)
{
	while (42)
	{
		if (++corewar->cycle && !(corewar->cycle % corewar->cycle_to_die))
			cycle_to_die(t_corewar *corewar);

	}
}