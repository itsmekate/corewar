#include "vm.h"

t_corewar	*new_corewar(void)
{
	t_corewar	*res;
	int			i;

	if ((res = (t_corewar *)malloc(sizeof(t_corewar))))
	{
		res->visual_mode = 0;
		res->dump = 0;
		res->cycles_to_die = CYCLE_TO_DIE;
		i = -1;
		while (++i <= MAX_PLAYERS)
			res->players[i] = NULL;
		res->players_num = 0;
		ft_memset(res->map, '\0', MEM_SIZE);
	}
	return (res);
}

t_player		*new_player(char *file)
{
	t_player *res;

	if ((res = (t_player *)malloc(sizeof(t_player))))
	{
		res->file = ft_strdup(file);
		res->start = 0;
	}
	return (res);
}

void			clear_player(t_player **player)
{
	free((*player)->file);
	free(*player);
	*player = NULL;
}

void				clear_corewar(t_corewar **corewar)
{
	int		i;

	i = 0;
	while ((*corewar)->players[i])
	{
		clear_player(&(*corewar)->players[i]);
		i++;
	}
	free(*corewar);
	*corewar = NULL;
}

////
////

void				print_corewar(t_corewar *corewar)
{
	printf("visual %i, dump %i\ncycles to die %i\n", corewar->visual_mode,
		corewar->dump, corewar->cycles_to_die);
	int i = -1;
	printf("players num %i\n", corewar->players_num);
	while (++i < corewar->players_num)
		printf("%s\n", corewar->players[i]->file);
	//printf("%s\n", );
}
