#include "../vm.h"

static void		dir_load(t_corewar *corewar, t_process *process)
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
}

static void		ind_load(t_corewar *corewar, t_process *process)
{
	(void)corewar;
	(void)process;
}

void			load(t_corewar *corewar, t_process *process)
{
	char	codage;

	codage = corewar->map[get_index(process->position + 1)].value & 0xff;
	printf("%02x\n", (codage & 0xff) >> 6);
	sleep(1);
	move_process(2, process, corewar);
	if (((codage & 0xff) >> 6) == DIR_CODE)
		dir_load(corewar, process);
	else if (((codage & 0xff) >> 6) == IND_CODE)
		ind_load(corewar, process);
	else
		printf("error\n");
	//
	printf("load\n");
	sleep(2);
	//
}