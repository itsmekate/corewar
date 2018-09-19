#include "../vm.h"

unsigned int	ldi(unsigned int arg1, unsigned int arg2, t_process *process,
	t_corewar *corewar)
{
	int				move;
	unsigned int	res;

	move = 2;
	arg1 = get_value(arg1, process, corewar, &move);
	arg2 = get_value(arg2, process, corewar, &move);
	res = get_arg(4, process->position + (arg1 + arg2), corewar);
	printf("move %i\n", move);
	move_process(move, process, corewar);
	return (res);
}

void			load_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];

	printf("load_index\n");
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	printf("%i;%i;%i\n", arg[0], arg[1], arg[2]);
	if (arg[0] > IND_CODE || arg[1] > DIR_CODE || arg[2] > REG_CODE ||
		!arg[0] || !arg[1] || !arg[2])
	{
		printf("error\n");
		return ;
	}
	arg[0] = ldi(arg[0], arg[1], process, corewar);
	arg[2] = get_arg(1, process->position, corewar);
	printf("regystry index %i\n", arg[2]);
	printf("%08x\n", arg[0]);
	if (arg[2] < REG_NUMBER)
		process->reg[arg[2]] = arg[0];
	move_process(1, process, corewar);
	sleep(1);
}