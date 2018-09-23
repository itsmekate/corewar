#include "../vm.h"

void			load_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	short 			arg1;
	short			arg2;

	// printf("load_index\n");
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] > IND_CODE || arg[1] > DIR_CODE || arg[2] > REG_CODE ||
		!arg[0] || !arg[1] || !arg[2])
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	arg1 = arg[0];
	arg2 = arg[1];
	arg1 = get_value(arg1, process, corewar, &move);
	arg2 = get_value(arg2, process, corewar, &move);
	arg[0] = get_arg(4, process->position + (arg1 + arg2) % IDX_MOD, corewar);
	arg[2] = get_arg(1, process->position + move, corewar);
	if (arg[2] < REG_NUMBER)
		process->reg[arg[2]] = arg[0];
	// printf("registry %i, value %08x\n", arg[2], arg[0]);
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
}