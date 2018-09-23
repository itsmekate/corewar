#include "../vm.h"

void			store(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;

	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] != REG_CODE || !arg[1] || arg[1] > IND_CODE || arg[1] == DIR_CODE || arg[2])
	{
		error_codage(&arg[0], process, corewar);
		return ;
	}
	move = 2;
	arg[0] = get_value(arg[0], process, corewar, &move);
	if (arg[1] == REG_CODE && arg[2] < REG_NUMBER)
	{
		arg[2] = get_value(arg[1], process, corewar, &move);
		process->reg[arg[2]] = arg[0];
	}
	else if (arg[1] == IND_CODE)
	{
		arg[2] = get_arg(2, process->position + move, corewar);
		set_unsigned_int(arg[0], get_index(process->position + (short)arg[2] % IDX_MOD),
			corewar, process->player);
	}
	log_move(corewar, process, move + 2);
	move_process(move + 2, process, corewar);
}