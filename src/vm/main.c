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

void		usage(char *program_name)
{
	ft_putstr("\nUsage: ");
	ft_putstr(program_name);
	ft_putstr(" [-v N -s N -d N -visual -debug] [-n N] champion.cor ..");
	ft_putstr("\n    -v N\t\tverbosity mod\n\n\tN: ");
	ft_putstr("(verbosity lvls can be added together to enable several)\n");
	ft_putstr("\t0   show only essentials\n");
	ft_putstr("\t1   show lives\n");
	ft_putstr("\t2   show cycles\n");
	ft_putstr("\t4   show operations\n");
	ft_putstr("\t8   show deathes\n");
	ft_putstr("\t16  show process carrige movements\n");
	ft_putstr("\t32  show aff result (ignore with -v 4)\n");
	ft_putstr("\n    -n [1 - 200]\tset player number ");
	ft_putstr("(numbers can`t duplicate)\n");
	ft_putstr("    -s N\t\truns N cycles, dumps memory, pauses, then repeats");
	ft_putstr("\n    -d N\t\tdumps memory after N cycles then exits");
	ft_putstr("\n    -visual\t\tturn on ncurses visual mod");
	ft_putstr("\n    -debug\t\tturn on debug mod");
	ft_putstr("\n\n    Can handle from 1 to 4 champions\n\n");
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
