#include "../vm.h"

void			ft_or(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[2] != REG_CODE || !arg[0] || arg[0] > IND_CODE || !arg[1] || arg[1] > IND_CODE)
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	arg[0] = get_value(arg[0], process, corewar, &move);
	arg[1] = get_value(arg[1], process, corewar, &move);
	arg[2] = get_arg(1, process->position + move, corewar);
	if (arg[2] < REG_NUMBER)
		process->reg[arg[2]] = arg[0] | arg[1];
	if (!process->reg[arg[2]])
		process->carry = 1;
	else
		process->carry = 0;
	log_move(corewar, process, ++move);
	move_process(move, process, corewar);
}