#include "../vm.h"

void			long_fork(t_corewar *corewar, t_process *process)
{
	printf("long_fork %i\n", corewar->cycle);
	sleep(1);
	//exit(1);
	(void)corewar;
	(void)process;
}