#include "../vm.h"

static unsigned int		dir_load(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;
	int				reg;

	dir = get_arg(4, process->position + 2, corewar);
	reg = get_arg(1, process->position + 6, corewar);
	//printf("reg index = %i\n", reg);
	//printf("%08x\n", dir);
	if (reg >= 0 && reg < REG_NUMBER)
		process->reg[reg] = dir;
	log_move(corewar, process, 7);
	move_process(7, process, corewar);
	return (dir);
}

static unsigned int		ind_load(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;
	short			ind;
	int				reg;

	ind = get_arg(2, process->position + 2, corewar);
	dir = get_arg(4, process->position + ind % IDX_MOD, corewar);
	reg = get_arg(1, process->position + 3, corewar);
	if (reg >= 0 && reg < REG_NUMBER)
		process->reg[reg] = dir;
	log_move(corewar, process, 5);
	move_process(5, process, corewar);
	return (dir);
}

void					load(t_corewar *corewar, t_process *process)
{
	char			codage;
	unsigned int	load;

	//
	//printf("load\n");
	//
	codage = get_arg(1, process->position + 1, corewar);
	load = 0;
	if (((codage & 0xff) >> 6) == DIR_CODE)
		load = dir_load(corewar, process);
	else if (((codage & 0xff) >> 6) == IND_CODE)
		load = ind_load(corewar, process);
	else
	{
		//print_map(corewar);
		//printf("load\n");
		//printf("position %i, cycle %ju\n", process->position, corewar->cycle);
		//printf("error\n");
		//exit(1);
		log_move(corewar, process, 2);
		move_process(2, process, corewar);
		return ;
	}
	if (!load)
		process->carry = 1;
	else
		process->carry = 0;
	//sleep(2);
}