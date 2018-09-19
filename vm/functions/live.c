#include "../vm.h"

void			player_alive(unsigned int number, t_corewar *corewar)
{
	int		i;

	i = -1;
	printf("number %u\n", number);
	while (++i < corewar->players_num)
	{
		if (0xffffffff - corewar->players[i]->number + 1 == number)
		{
			printf("alive\n");
			corewar->players[i]->process_num++;
		}
	}
}

void			live(t_corewar *corewar, t_process *process)
{
	unsigned int	dir;

	print_map(corewar);
	printf("live\n");
	process->alive = 1;
	dir = get_arg(4, process->position + 1, corewar);
	player_alive(dir, corewar);
	move_process(5, process, corewar);
	sleep(1);
}
