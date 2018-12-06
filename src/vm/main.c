/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:43:56 by dzabrots          #+#    #+#             */
/*   Updated: 2018/12/05 17:43:59 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	usage(char *program_name)
{
	ft_putstr("\nUsage: ");
	ft_putstr(program_name);
	ft_putendl(" [-d N -s N -v N | -visual] <champion1.cor> <...>");
	ft_putendl(" ");
	ft_putendl(" -- TEXT OUTPUT MODE ---------------------------------------");
	ft_putendl(" ");
	ft_putendl("    -d N      : Dumps memory after N cycles then exits");
	ft_putendl("    -s N      : Visual mod after N cycles");
	ft_putendl("    -v N      : Verbosity. Levels (N): ");
	ft_putendl("                - 1 : Show lives");
	ft_putendl("                - 2 : Show cycles");
	ft_putendl("                - 4 : Show operations");
	ft_putendl("                - 8 : Show deaths");
	ft_putendl("                - 16 : Show PC movements (Except for jumps)");
	ft_putendl(" ");
	ft_putendl(" -- NCURSES OUTPUT MODE -------------------------------------");
	ft_putendl(" ");
	ft_putendl("    -visual   : Ncurses output mode");
	ft_putendl(" ");
	exit(0);
}

int			main(int argc, char **argv)
{
	t_corewar	*corewar;

	if (argc < 2)
		usage(argv[0]);
	if ((corewar = create_corewar(argv)) && corewar->players_num > 0)
	{
		if (corewar->players_num > 0)
		{
			print_contestants(corewar);
			grand_cycle(corewar);
		}
		del_visual(corewar->win);
		clear_corewar(&corewar);
	}
	else
		usage(argv[0]);
	return (0);
}
