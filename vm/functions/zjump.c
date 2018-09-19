#include "../vm.h"

void			zjump(t_corewar *corewar, t_process *process)
{
	unsigned int		dir;

	//
	printf("zjump\n");
	//				
	if (!process->carry)
	{
		printf("carry is absent\n");
		move_process(3, process, corewar);
		return;
	}
	dir = get_arg(2, process->position + 1, corewar);
	move_process(dir, process, corewar);
	sleep(2);
	print_map(corewar);
	sleep(4);

}