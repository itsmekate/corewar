# include "vm.h"

static void	usage(char *program_name)
{
	ft_putstr("Usage: ");
	ft_putstr(program_name);
	ft_putendl(" [-d N -s N -v N | -n --stealth] [-a] <champion1.cor> <...>");
    ft_putendl("-a        : Prints output from \"aff\" (Default is to hide it)");
	ft_putendl("#### TEXT OUTPUT MODE ##########################################################");
	ft_putendl("    -d N      : Dumps memory after N cycles then exits");
	ft_putendl("    -s N      : Runs N cycles, dumps memory, pauses, then repeats");
	ft_putendl("    -v N      : Verbosity levels, can be added together to enable several");
	ft_putendl("                - 0 : Show only essentials");
	ft_putendl("                - 1 : Show lives");
	ft_putendl("                - 2 : Show cycles");
	ft_putendl("                - 4 : Show operations (Params are NOT litteral ...)");
	ft_putendl("                - 8 : Show deaths");
	ft_putendl("                - 16 : Show PC movements (Except for jumps)");
	ft_putendl("#### NCURSES OUTPUT MODE #######################################################");
	ft_putendl("    -n        : Ncurses output mode");
	ft_putendl("    --stealth : Hides the real contents of the memory");
	ft_putendl("################################################################################");
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