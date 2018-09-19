#include "../vm.h"

unsigned int	get_value(unsigned int arg, t_process *process,
	t_corewar *corewar, int *move)
{
	if (arg == REG_CODE)
	{
		printf("REG_CODE\n");
		arg = get_arg(1, process->position + *move, corewar);
		*move = *move + 1;
		if (arg < REG_NUMBER)
			arg = process->reg[arg];
	}
	else if (arg == DIR_CODE)
	{
		printf("DIR_CODE\n");
		arg = get_arg(2, process->position + *move, corewar);
		*move = *move + 2;
	}
	else if (arg == IND_CODE)
	{
		printf("IND_CODE\n");
		arg = get_arg(2, process->position + *move, corewar);
		*move = *move + 2;
		arg = get_arg(4, process->position + arg % IDX_MOD, corewar);
	}
	return (arg);
}

unsigned int	ldi(unsigned int arg1, unsigned int arg2, t_process *process,
	t_corewar *corewar)
{
	int				move;
	unsigned int	res;

	move = 2;
	arg1 = get_value(arg1, process, corewar, &move);
	arg2 = get_value(arg2, process, corewar, &move);
	res = get_arg(4, process->position + (arg1 + arg2) % IDX_MOD, corewar);
	printf("move %i\n", move);
	move_process(move, process, corewar);
	return (res);
}

void			load_index(t_corewar *corewar, t_process *process)
{
	char			codage;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	print_map(corewar);
	printf("load_index\n");
	codage = get_arg(1, process->position + 1, corewar);
	arg1 = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg2 = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg3 = (codage & 0xff) >> 6;
	printf("%i;%i;%i\n", arg1, arg2, arg3);
	if (arg1 > IND_CODE || arg2 > DIR_CODE || arg3 > REG_CODE)
	{
		printf("error\n");
		return ;
	}
	arg1 = ldi(arg1, arg2, process, corewar);
	arg3 = get_arg(1, process->position, corewar);
	if (arg3 < REG_NUMBER)
		process->reg[arg3] = arg1;
	move_process(1, process, corewar);
	print_map(corewar);
	sleep(1);
}