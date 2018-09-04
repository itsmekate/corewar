#include "vm.h"

static int			is_flag(char *arg)
{
	if (ft_strequ(arg, "-n"))
		return (1);
	if (ft_strequ(arg, "-d"))
		return (2);
	return (0);
}

static void			add_player(char *name, t_corewar *corewar)
{
	corewar->players[corewar->players_num] = new_player(name);
	if (!parse_player(corewar->players[corewar->players_num]))
	{
		clear_corewar(&corewar);
		exit(0);
	}
	corewar->players_num++;
}

static void			get_starts(t_corewar *corewar)
{
	int		step;
	int		i;

	step = MEM_SIZE / corewar->players_num;
	i = 0;
	while (i < corewar->players_num)
	{
		corewar->players[i]->start = i * step;
		i++;
	}
}

t_corewar			*create_corewar(char **agrv)
{
	t_corewar	*res;
	int			flag;

	if ((res = new_corewar()))
	{
		while (*agrv)
		{
			if (!(flag = is_flag(*agrv)))
				add_player(*agrv, res);
			else if (flag == 1)
				res->visual_mode = 1;
			else if (flag == 2)
			{
				agrv++;
				res->dump = ft_atoi(*agrv);
			}
			agrv++;
		}
	}
	get_starts(res);
	return (res);
}