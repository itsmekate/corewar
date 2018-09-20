#include "vm.h"

static int			is_flag(char *arg)
{
	if (ft_strequ(arg, "-n"))
		return (1);
	if (ft_strequ(arg, "-d"))
		return (2);
	if (ft_strequ(arg, "-l"))
		return (3);
	if (ft_strequ(arg, "-s"))
		return (4);
	if (ft_strequ(arg, "-v"))
		return (5);
	return (0);
}

static void			add_player(char *name, t_corewar *corewar, int num)
{
	if (corewar->players_num >= MAX_PLAYERS)
	{
		ft_putendl_fd("ERROR: Too many champions", 2);
		clear_corewar(&corewar);
		exit(0);
	}
	corewar->players[corewar->players_num] = new_player(name);
	if (!parse_player(corewar->players[corewar->players_num]))
	{
		ft_putstr_fd("ERROR: Broken champion: ", 2);
		ft_putendl_fd(name, 2);
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
		i++;
	}
	ft_lstadd(&corewar->processes, obj_in_lst(
		create_process(player->start, player, corewar)));
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

static int			flag_value_handler(char ***argv)
{
	char	**buf;
	int		res;

	buf = *argv;
	if (is_number(*(buf + 1)))
	{
		res = ft_atoi(*(buf + 1));
		if (res > 0)
		{
			*argv = *argv + 1;
			return (res);
		}
		else
			return (0);
	}
	return (0);
}

static void			flag_handler(int flag, char ***agrv, t_corewar *res)
{
	if (flag == 2)
		res->dump = flag_value_handler(agrv);
	else if (flag == 3)
		res->verbal = flag_value_handler(agrv);
	else if (flag == 4)
		res->start = flag_value_handler(agrv);
	else if (flag == 5)
		res->visual_mode = 1;
}

t_corewar			*create_corewar(char **agrv)
{
	t_corewar	*res;
	int			flag;
	int			num;

	if ((res = new_corewar()))
	{
		num = 0;
		while (*agrv)
		{
			if (num || !(flag = is_flag(*agrv)))
			{
				add_player(*agrv, res, num);
				num = 0;
			}
			else if (flag == 1)
				num = flag_value_handler(&agrv);
			else
				flag_handler(flag, &agrv, res);
			agrv++;
		}
	}
	// res = NULL;
	// (void)agrv;
	get_starts(res);
	init_commands(res);
	return (res);
}