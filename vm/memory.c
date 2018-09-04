#include "vm.h"

static t_corewar	*new_corewar(void)
{
	t_corewar	*res;
	int			i;

	if ((res = (t_corewar *)malloc(sizeof(t_corewar))))
	{
		res->visual_mode = 1;
		res->dump = 0;
		res->cycles_to_die = CYCLE_TO_DIE;
		i = -1;
		while (++i <= MAX_PLAYERS)
			res->players[i] = NULL;
	}
	return (res);
}

t_player			*new_player(char *file)
{
	t_player *res;

	if ((res = (t_player *)malloc(sizeof(t_player))))
	{
		res->file = ft_strdup(file);
	}
	return (res);
}

void				clear_player(t_player **player)
{
	free((*player)->file);
	free(*player);
	*player = NULL;
}

t_corewar			*create_corewar(char **agrv)
{
	t_corewar *res;

	res = new_corewar();
	(void)agrv;
	return (res);
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
