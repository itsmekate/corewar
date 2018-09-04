#include "vm.h"

static int			is_flag(char *arg)
{
	if (ft_strequ(arg, "-n"))
		return (1);
	if (ft_strequ(arg, "-d"))
		return (2);
	return (0);
}

static void			add_player(char *name)
{
	
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
			else if (flag = 2)
			{
				agrv++;
				res->dump = get_int(*agrv);
			}
			agrv++;
		}
	}
	return (res);
}