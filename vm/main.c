# include "vm.h"

static void	usage(char *program_name)
{
	ft_putstr(program_name);
	ft_putstr(" [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	exit(0);
}

int			main(int argc, char **argv)
{
	t_corewar	*corewar;

	if (argc < 2)
		usage(argv[0]);
	if ((corewar = create_corewar(++argv)))
	{
		print_contestants(corewar);
		grand_cycle(corewar);
		// print_log(corewar->log);
		// dump_map(corewar);
		// print_winner(get_winner(corewar));
		clear_corewar(&corewar);
		// while (42)
		// {
		// 	;
		// }
	}
	return 0;
}