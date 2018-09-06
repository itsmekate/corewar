#include "vm.h"

int				is_number(t_corewar *corewar, char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
		{
			ft_putendl_fd("ERROR: Wrong value", 2);
			clear_corewar(&corewar);
			exit(0);
		}
		s++;
	}
	return (1);
}

static int		is_exist(t_corewar *corewar, int num)
{
	int i;

	i = 0;
	while (i < corewar->players_num)
	{
		if (corewar->players[i]->number == num)
			return (1);
		i++;
	}
	return (0);
}

int				get_number(t_corewar *corewar, int num)
{
	int ret;

	if (num < 0)
	{
		if (!corewar->players_num)
			ret = 1;
		else
		{
			ret = corewar->players[corewar->players_num - 1]->number + 1;
			while (is_exist(corewar, ret))
				ret++;
		}
	}
	else
	{
		ret = num;
		if (is_exist(corewar, ret))
		{
			ft_putendl_fd("ERROR: Wrong champion number", 2);
			clear_corewar(&corewar);
			exit(0);
		}
	}
	return (ret);
}