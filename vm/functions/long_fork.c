#include "../vm.h"

void			long_fork(t_corewar *corewar, t_process *process)
{
	//unsigned int	arg[3];
	short			arg1;
	 t_process		*res;

	// ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	// get_types(&arg[0], process, corewar);
	// //printf("%u,%u,%u\n", arg[0], arg[1], arg[2]);
	// if ((arg[2] == DIR_CODE && !arg[1] && !arg[0]) ||
	// 	(arg[1] == DIR_CODE && !arg[2] && !arg[0]) ||
	// 	(arg[0] == DIR_CODE && !arg[1] && !arg[2]) ||
	// 	get_arg(1, process->position + 1, corewar))
	// {
		//printf("long_fork\n");
		arg1 = get_arg(2, process->position + 1, corewar);
		res = copy_process(process);
		ft_lstadd(&corewar->processes, obj_in_lst(res));
		move_process(arg1, res, corewar);
	//}
	log_move(corewar, process, 3);
	move_process(3, process, corewar);
}