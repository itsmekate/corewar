#include "vm.h"

t_process	*new_procces()
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
