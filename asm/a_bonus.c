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

void		print_commands(t_cmnd *c, t_asm a)
{
	int		sum;
	int		i;

	sum = 0;
	i = 0;
	while (c)
	{
		ft_printf("%-5d(%-3d) :\t", sum, c->n_byte);
		if (c->label)
		{
			ft_printf("%s:", c->label);
			if (c->command_name < 0)
				ft_printf("\n\n");
		}
		if (c->command_name > 0)
		{
			i = 0;
			ft_printf("\t%s:", a.op_tab[c->command_name - 1].name);
			while (c->arg.arg_arr[i].type && i < 3)
			{
				ft_printf("\t\t");
				if (c->arg.arg_arr[i].type == 1)
					ft_printf("r");
				else if (c->arg.arg_arr[i].type == 2)
					ft_printf("%%");
				if (c->arg.arg_arr[i].text)
					ft_printf(":%s", c->arg.arg_arr[i].text);
				else
					ft_printf("%d", c->arg.arg_arr[i].value);
				i++;
			}
			ft_printf("\n\n");
		}
		sum += c->n_byte;
		c = c->next;
	}
}

void		a_bonus(t_asm a)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", sum_exec(a.command));
	ft_printf("Name : \"%s\"\n", a.bot_name);
	ft_printf("Comment : \"%s\"\n\n", a.bot_comment);
	print_commands(a.command, a);
}
