#include "../vm.h"

void			store(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] != REG_CODE || !arg[1] || arg[1] > IND_CODE || arg[1] == DIR_CODE || arg[2])
	{
		//printf("error %ju\n", corewar->cycle);
		log_move(corewar, process, 2);
		move_process(2, process, corewar);
		return ;
	}

	// print_map(corewar);
	// printf("store\n");
	// //sleep(4);
	// printf("%ju\n", corewar->cycle);
	//exit(1);
}