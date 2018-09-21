#include "../vm.h"

void			long_load_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[1] || arg[1] > IND_CODE || arg[1] > DIR_CODE ||
		!arg[0] || arg[0] > IND_CODE)
	{
		//printf("error %ju\n", corewar->cycle);
		log_move(corewar, process, 2);
		move_process(2, process, corewar);
		return ;
	}
	print_map(corewar);
	// 	printf("long_load_index\n");
	// 	printf("position %i\n", process->position);
	// 	printf("error\n");
	// 	//printf("%i;%i;%i\n", arg[0], arg[1], arg[2]);
	// 	printf("%ju\n", corewar->cycle);
	// 	//exit(2);
	// sleep(1);
}
