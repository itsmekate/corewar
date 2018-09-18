#include "../vm.h"

void			player_alive(int number, t_corewar *corewar)
{
	int		i;

	i = -1;
	while (++i < corewar->players_num)
	{
		if (corewar->players[i]->number == number)
			corewar->players[i]->process_num++;
	}
}

void			live(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;

	printf("live\n");
	process->alive = 1;
	dir = get_arg(4, process->position + 1, corewar);
	move_process(5, process, corewar);
	sleep(1);
}