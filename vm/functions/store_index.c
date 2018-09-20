#include "../vm.h"

void			store_index(t_corewar *corewar, t_process *process)
{
	unsigned int	arg[3];
	int				move;
	short 			index;

	//printf("store_index\n");
	//print_map(corewar);
	ft_memset(arg, '\0', sizeof(unsigned int) * 3);
	get_types(&arg[0], process, corewar);
	if (arg[0] != REG_CODE || (arg[2] != REG_CODE && arg[2] != DIR_CODE) || !arg[1]
		|| arg[1] > IND_CODE)
	{
		// print_map(corewar);
		// printf("store_index\n");
		// printf("position %i\n", process->position);
		// printf("error\n");
		// printf("%i;%i;%i\n", arg[0], arg[1], arg[2]);
		// printf("%ju\n", corewar->cycle);
		// sleep(2);
		move_process(8, process, corewar);
		//print_map(corewar);
		//exit(1);
		return ;
	}
	move = 2;
	arg[0] = get_value(arg[0], process, corewar, &move);
	//printf("value is %08x\n", arg[0]);
	arg[1] = get_value(arg[1], process, corewar, &move);
	arg[2] = get_value(arg[2], process, corewar, &move);
	//printf("1 = %hhi, 2 = %hhi\n", (char)arg[1], (char)arg[2]);
	//printf("1 = %hi, 2 = %hi\n", (short)arg[1], (short)arg[2]);
	//printf("1 = %u, 2 = %u\n", arg[1], arg[2]);
	index = (short)arg[1] + (short)arg[2];
	//printf("%hhi; %i\n", (char)index, (char )index % IDX_MOD);
	set_unsigned_int(arg[0], get_index(process->position + index % IDX_MOD), corewar, process->player);
	// if (arg2 == DIR_CODE && arg3 == DIR_CODE)
	//  	reg_dir_dir(arg1, corewar, process);
	//  else
	//  	printf("I DONT KNOW WHAT TO DO!!!!\n");
	// int i = -1;

	// while (++i < 16)
	// {
	// 	printf("%08x\n", process->reg[i]);
	// }
	move_process(move, process, corewar);
	//sleep(3);
}