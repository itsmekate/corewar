#include "../vm.h"

static void		reg_dir_dir(unsigned int arg1, t_corewar *corewar, t_process *process)
{
	unsigned int	arg2;
	unsigned int	arg3;

	printf("reg_dir_dir\n");
	arg2 = get_arg(2, process->position + 3, corewar);
	arg3 = get_arg(2, process->position + 5, corewar);
	set_unsigned_int(arg1, get_index(process->position + (arg2 + arg3)), corewar, process->player);

	//set_point(&corewar->map[get_index(process->position + (arg2 + arg3))], arg1, process->player);
	print_map(corewar);
	move_process(7, process, corewar);
}

void			store_index(t_corewar *corewar, t_process *process)
{
	char			codage;
	unsigned int	arg1;
	int				arg2;
	int				arg3;

	printf("store_index\n");
	codage = get_arg(1, process->position + 1, corewar);
	arg1 = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg2 = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg3 = (codage & 0xff) >> 6;
	printf("1 %i, 2 %i, 3 %i\n", arg1, arg2, arg3);
	if (arg1 != REG_CODE || (arg3 != REG_CODE && arg3 != DIR_CODE))
	{
		printf("error\n");
		return ;
	}
	arg1 = get_arg(1, process->position + 2, corewar);
	printf("index registry %i\n", arg1);
	if (arg1 < REG_NUMBER)
		arg1 = process->reg[arg1];
	else
		return ;
	printf("arg1 = %08x\n", arg1);

	if (arg2 == DIR_CODE && arg3 == DIR_CODE)
	 	reg_dir_dir(arg1, corewar, process);
	 else
	 	printf("I DONT KNOW WHAT TO DO!!!!\n");
	sleep(1);
}