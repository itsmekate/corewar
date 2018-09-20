#include "../vm.h"

void			addition(t_corewar *corewar, t_process *process)
{
	//printf("addition\n");


	char			codage;
	unsigned int	arg1;
	unsigned int	arg2;
	unsigned int	arg3;

	codage = get_arg(1, process->position + 1, corewar);
	arg1 = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg2 = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg3 = (codage & 0xff) >> 6;
	if (arg1 != REG_CODE || arg2 != REG_CODE || arg3 != REG_CODE)
	{
		print_map(corewar);
		printf("addition\n");
		printf("position %i\n", process->position);
		printf("error\n");
		exit(1);
	}
	arg1 = get_arg(1, process->position + 2, corewar);
	arg2 = get_arg(1, process->position + 3, corewar);
	arg3 = get_arg(1, process->position + 4, corewar);
	if (arg1 >= REG_NUMBER || arg2 >= REG_NUMBER || arg3 >= REG_NUMBER)
		return;
	arg1 = process->reg[arg1];
	arg2 = process->reg[arg2];
	process->reg[arg3] = arg1 + arg2;
	if (process->reg[arg3])
		process->carry = 0;
	else
		process->carry = 1;
	//printf("res = %u\n", process->reg[arg3]);
	move_process(5, process, corewar);
	//sleep(1);
}
