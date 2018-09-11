#include "asm.h"

int			a_flag(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-a"))
		{
			if (i != argc - 1)
				return (argc - 1);
			else
				return (i - 1);
		}
		i++;
	}
	return (0);
}

void		cmnd_labl_size(t_cmnd *c, t_asm a, int k)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_printf("\n\t\t    ");
	if (a.op_tab[c->command_name - 1].acb)
		ft_printf("%-4d%-6d", c->command_name, count_codage(c->arg));
	else
		ft_printf("%-10d", c->command_name);
	while (c->arg.arg_arr[i].type && i < 3)
	{
		if (c->arg.arg_arr[i].type > 1 && k == 0)
		{
			j = 0;
			while (j < a.op_tab[c->command_name - 1].label_size - 1)
			{
				ft_printf("%-4d", 0);
				j++;
			}
			ft_printf("%-*d", 16 - j * 4, c->arg.arg_arr[i].value);
		}
		else
			ft_printf("%-16d", c->arg.arg_arr[i].value);
		i++;
	}
}

void		print_commands(t_cmnd *c, t_asm a)
{
	int		sum;
	int		i;

	sum = 0;
	i = 0;
	while (c)
	{
		if (c->label)
		{
			ft_printf("%-10d :\t", sum);
			ft_printf("%s:", c->label);
			ft_printf("\n");
		}
		if (c->command_name > 0)
		{
			ft_printf("%-5d(%-3d) :\t    %-10s", sum, c->n_byte, a.op_tab[c->command_name - 1].name);
			i = 0;
			while (c->arg.arg_arr[i].type && i < 3)
			{
				if (c->arg.arg_arr[i].type == 1)
					ft_printf("r");
				else if (c->arg.arg_arr[i].type == 2)
					ft_printf("%%");
				if (c->arg.arg_arr[i].text)
					ft_printf(":%-15s", c->arg.arg_arr[i].text);
				else
				{
					if (c->arg.arg_arr[i].type == 3)
						ft_printf("%-16d", c->arg.arg_arr[i].value);
					else
						ft_printf("%-15d", c->arg.arg_arr[i].value);
				}
				i++;
			}
			cmnd_labl_size(c, a, 0);
			cmnd_labl_size(c, a, 1);
			ft_printf("\n\n");
		}
		sum += c->n_byte;
		c = c->next;
	}
}

void		a_bonus(t_asm a)
{
	ft_printf("Dumping annotato	ed program on standard output\n");
	ft_printf("Program size : %d bytes\n", sum_exec(a.command));
	ft_printf("Name : \"%s\"\n", a.bot_name);
	ft_printf("Comment : \"%s\"\n\n", a.bot_comment);
	print_commands(a.command, a);
}
