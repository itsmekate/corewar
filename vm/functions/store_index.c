#include "../vm.h"

// static void		reg_dir_dir(unsigned int arg1, t_corewar *corewar, t_process *process)
// {
// 	unsigned int	arg2;
// 	unsigned int	arg3;

// 	printf("reg_dir_dir\n");
// 	arg2 = get_arg(2, process->position + 3, corewar);
// 	arg3 = get_arg(2, process->position + 5, corewar);
// 	set_unsigned_int(arg1, get_index(process->position + (arg2 + arg3)), corewar, process->player);

// 	//set_point(&corewar->map[get_index(process->position + (arg2 + arg3))], arg1, process->player);
// 	move_process(7, process, corewar);
// }

void			store_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	short 			index;

	printf("store_index\n");
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	printf("%i;%i;%i\n", arg[0], arg[1], arg[2]);
	if (arg[0] != REG_CODE || (arg[2] != REG_CODE && arg[2] != DIR_CODE) || !arg[1]
		|| arg[1] > IND_CODE)
	{
		printf("error\n");
		return ;
	}
	move = 2;
	arg[0] = get_value(arg[0], process, corewar, &move);
	printf("value is %08x\n", arg[0]);
	arg[1] = get_value(arg[1], process, corewar, &move);
	arg[2] = get_value(arg[2], process, corewar, &move);
	index = (short)arg[1] + (short)arg[2];
	set_unsigned_int(arg[0], get_index(process->position + index % IDX_MOD), corewar, process->player);
	int i = -1;

	while (++i < 16)
	{
		printf("%08x\n", process->reg[i]);
	}
	move_process(move, process, corewar);
	sleep(3);
}