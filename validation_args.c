#include "asm.h"

int			find_label_num(char *str, t_cmnd *cmnds)
{
	int		res;

	res = 0;
	while (cmnds)
	{
		if (cmnds->label)
		{
			if (!strcmp(str, cmnds->label))
				return (res);
		}
		res += cmnds->n_byte;
		cmnds = cmnds->next;
	}
	return (-1);
}

int			label_to_numbers(t_cmnd	*cmnds)
{
	t_cmnd	*tmp;
	int		i;
	int		res;
	int		tmp_res;

	i = 0;
	res = 0;
	tmp = cmnds;
	while (cmnds)
	{
		i = 0;
		if (cmnds->command_name == -1)
		{
			cmnds = cmnds->next;
			continue;
		}
		while (cmnds->arg.arg_arr[i].type && i < 3)
		{
			if (cmnds->arg.arg_arr[i].text)
			{
				if ((tmp_res = find_label_num(cmnds->arg.arg_arr[i].text, tmp)) == -1)
				{
					ft_strdel(&cmnds->arg.arg_arr[i].text);
					return (0);
				}
				cmnds->arg.arg_arr[i].value = tmp_res - res;
				ft_strdel(&cmnds->arg.arg_arr[i].text);
			}
			i++;
		}
		res += cmnds->n_byte;
		cmnds = cmnds->next;
	}
	return (1);
}

int     validation_args(t_cmnd *c, t_asm *a)
{
	int i;
	int j;

	i = 0;
	if (!c->arg.arg_arr[i].type)
		return (0);
	while (c->arg.arg_arr[i].type && i < 3)
	{
		j = 0;
		while (a->op_tab[c->command_name - 1].params[i][j] && j <= 3)
		{
			if (c->arg.arg_arr[i].type == a->op_tab[c->command_name - 1].params[i][j])
				break;
			else
			{
				j++;
				if (!a->op_tab[c->command_name - 1].params[i][j])
					return (0);
			}
		}
		if (!a->op_tab[c->command_name - 1].params[i][j])
			return (0);
		i++;
	}
	return (1);
}
