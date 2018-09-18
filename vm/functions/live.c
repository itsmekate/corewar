#include "../vm.h"

void			live(t_corewar *corewar, t_process *process)
{
	char			res[4];
	unsigned int	dir;
	int				i;

	printf("live\n");
	process->alive = 1;
	move_process(1, process, corewar);


	ft_memset(res, '\0', 4);
	i = -1;
	while (++i < 4)
		res[3 - i] = corewar->map[get_index(process->position + i)].value & 0xff;
	dir = *(unsigned int *)res;


	sleep(1);
	(void)corewar;
	(void)process;
}