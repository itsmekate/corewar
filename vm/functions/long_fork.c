#include "../vm.h"

void			long_fork(t_corewar *corewar, t_process *process)
{
	short			arg1;
	 t_process		*res;

		
	arg1 = get_arg(2, process->position + 1, corewar);
	res = copy_process(process);
	ft_lstadd(&corewar->processes, obj_in_lst(res));
	move_process(arg1, res, corewar);
	log_move(corewar, process, 3);
	move_process(3, process, corewar);
}