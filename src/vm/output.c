/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 16:57:35 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/30 16:57:57 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	new_line(void)
{
	ft_putstr("\n");
	return (0);
}

static int 	print_row_num(int x)
{
	char 	*str;

	str = ft_itoa_base(x, 16, 4);
	ft_putstr("0x");
	ft_putstr(str);
	ft_putstr(" : ");
	free(str);
	return (64);
}

void 		dump_map(t_corewar *corewar)
{
	int		i;
	int		n;
	int		x;
	char	*str;

	i = 0;
	n = 0;
	x = 0;
	while (i < MEM_SIZE)
	{
		if (n == 64)
			n = new_line();
		if (!n)
			x += print_row_num(x);
		n++;
		str = ft_itoa_base(corewar->map[i].value & 0xff, 16, 2);
		ft_putstr(str);
		ft_putstr(" ");
		free(str);
		corewar->map[i].is_new = 0;
		i++;
	}
	ft_putstr("\n");
}

void			print_contestants(t_corewar *corewar)
{
	int			i;
	t_player	*player;

	ft_putstr("Introducing contestants...\n");
	i = 0;
	while (i < corewar->players_num)
	{
		player = corewar->players[i];
		ft_putstr("* Player ");
		ft_putnbr(player->number);
		ft_putstr(", weighing ");
		ft_putnbr(player->size);
		ft_putstr(" bytes, \"");
		ft_putstr(player->name);
		ft_putstr("\" (\"");
		ft_putstr(player->comment);
		ft_putstr("\") !\n");
		i++;
	}
}

void			print_winner(t_player *winner)
{
	if (winner)
	{
		ft_putstr("Contestant ");
		ft_putnbr(winner->number);
		ft_putstr(", \"");
		ft_putstr(winner->name);
		ft_putstr("\", has won !\n");
	}
}

t_player		*get_winner(t_corewar *corewar)
{
	int			i;
	t_player	*player;

	i = 0;
	while (i < corewar->players_num)
	{
		player = corewar->players[i];
		if (player->number == corewar->last_alive)
			return (corewar->players[i]);
		i++;
	}
	return (NULL);
}




















