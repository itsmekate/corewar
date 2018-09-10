#include "vm.h"

t_process	*new_procces(void)
{
	t_process *res;
	if ((res = (t_process *)malloc(sizeof(t_process))))
		ft_memset(res, '\0', sizeof(t_process));
	return (res);
}

void		clear_process(t_process **process, size_t size)
{
	ft_memset(*process, '\0', size);
	free(*process);
	*process = NULL;
}

void		kill_process(t_corewar *corewar, t_process *process)
{
	t_list		*lst;
	t_list		*lst1;
	t_list		*lst0;
	t_process	*pr;

	lst = corewar->process;
	lst0 = NULL:
	while (lst)
	{
		lst1 = lst->next;
		pr = lst->content;
		if (pr == process)
		{
			if (!lst0)
				corewar->process = lst1;
			else
				lst0->next = lst1;
			clear_process(pr);
			free(lst);
			lst = NULL;
			return ;
		}
		lst0 = lst;
		lst = lst1;
	}
}