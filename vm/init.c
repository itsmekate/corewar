#include "vm.h"

static int			is_flag(char *arg)
{
	if (ft_strequ(arg, "-n"))
		return (1);
	if (ft_strequ(arg, "-d"))
		return (2);
	return (0);
}

static void			add_player(char *name, t_corewar *corewar, int num)
{
	corewar->players[corewar->players_num] = new_player(name);
	if (corewar->players_num >= MAX_PLAYERS)
	{
		ft_putendl_fd("ERROR: Too many champions", 2);
		clear_corewar(&corewar);
		exit(0);
	}
	else if (!parse_player(corewar->players[corewar->players_num]))
	{
		clear_corewar(&corewar);
		exit(0);
	}
	corewar->players[corewar->players_num]->number = get_number(corewar, num);
	corewar->players_num++;
}

static void			set_exec(t_corewar *corewar, t_player *player)
{
	int		i;

	i = 0;
	while (i < player->size)
	{
		if (i + player->start >= MEM_SIZE)
			return ;
		set_point(&corewar->map[i + player->start], player->exec[i], player);
		ft_lstadd(&corewar->processes, obj_in_lst(
			create_proccess(player->start, player, corewar)));
		i++;
	}
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
		set_exec(corewar, corewar->players[i]);
		i++;
	}
}

t_corewar			*create_corewar(char **agrv)
{
	t_corewar	*res;
	int			flag;
	int			num;

	if ((res = new_corewar()))
	{
		num = -1;
		while (*agrv)
		{
			if (!(flag = is_flag(*agrv)))
			{
				add_player(*agrv, res, num);
				num = -1;
			}
			else if (flag == 1)
				num = is_number(res, *(++agrv)) ? ft_atoi(*agrv) : 0;
			else if (flag == 2)
				res->dump = is_number(res, *(++agrv)) ? ft_atoi(*agrv) : 0;
			agrv++;
		}
	}
	get_starts(res);
	return (res);
}