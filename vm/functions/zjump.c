#include "../vm.h"

void			zjump(t_corewar *corewar, t_process *process)
{
	char			res[2];
	int				dir;
	int				i;

	//
	printf("zjump\n");
	//				
	if (!process->carry)
		return;
	move_process(1, process, corewar);
	ft_memset(res, '\0', 2);
	dir = 0;
	i = -1;
	while (++i < 2)
	{
		dir += corewar->map[get_index(process->position + i)].value & 0xff;
		// printf("dir == %x\n", dir);
		dir = dir << (8 * (1 - i));
	}
	//dir = *(int *)res;
	// printf("%i\n", dir);
	move_process(dir % IDX_MOD - 1, process, corewar);
	sleep(2);
}