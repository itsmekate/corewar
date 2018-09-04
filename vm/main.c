# include "vm.h"

void	usage(char *program_name)
{
	ft_putstr(program_name);
	ft_putstr(" [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	exit(0);
}

int		main(int argc, char const *argv[])
{
	t_corewar	*corewar;

	if (argc < 2)
		usage(argv[0]);
	if ((corewar = create_corewar(argv)))
	{
		clear_corewar(&corewar);
	}
	return 0;
}