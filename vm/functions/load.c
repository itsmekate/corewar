#include "../vm.h"

static unsigned int		dir_load(t_corewar *corewar, t_process *process)
{
	char			res[4];
	unsigned int	load;
	int				i;

	ft_memset(res, '\0', 4);
	i = -1;
	while (++i < 4)
		res[3 - i] = corewar->map[get_index(process->position + i)].value & 0xff;
	load = *(unsigned int *)res;
	i = corewar->map[get_index(process->position + 4)].value & 0xff;
	if (i >= 0 && i < REG_NUMBER)
		process->reg[i] = load;
	move_process(5, process, corewar);
	return (load);
}

static unsigned int		ind_load(t_corewar *corewar, t_process *process)
{
	//char			res[4];
	unsigned int	load;
	int				ind;
	int				i;

	//ft_memset(res, '\0', 4);
	ind = 0;
	i = -1;
	while (++i < 2)
	{
		ind += corewar->map[get_index(process->position + i)].value & 0xff;
		ind = ind << (8 * (1 - i));
	}
	ind = ind % IDX_MOD;
	move_process(ind, process, corewar);
	load = dir_load(corewar, process);
	return (load);
}

void					load(t_corewar *corewar, t_process *process)
{
	char			codage;
	unsigned int	load;

	//
	printf("load\n");
	//
	codage = corewar->map[get_index(process->position + 1)].value & 0xff;
	printf("arg = %x\n", codage & 0xff);
	move_process(2, process, corewar);
	load = 0;
	if (((codage & 0xff) >> 6) == DIR_CODE)
		load = dir_load(corewar, process);
	else if (((codage & 0xff) >> 6) == IND_CODE)
		load = ind_load(corewar, process);
	else
		printf("error\n");
	if (!load)
		process->carry = 1;
	else
		process->carry = 0;
	sleep(2);
}