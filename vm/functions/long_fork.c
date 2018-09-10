#include "../vm.h"

void			long_fork(t_corewar *corewar, t_process *process)
{
	printf("long_fork\n");
	sleep(1);
	(void)corewar;
	(void)process;
}