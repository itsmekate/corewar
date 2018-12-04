/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:34:01 by kprasol           #+#    #+#             */
/*   Updated: 2018/11/26 15:34:18 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		clear_field(t_corewar *c)
{
	t_field f;

	f.col = 1;
	f.row = 1;
	wattron(c->win.field, 4);
	while (f.row <= MEM_SIZE / 64)
	{
		f.col = 1;
		while (f.col < 193)
		{
			mvwprintw(c->win.field, f.row, f.col, " ");
			f.col++;
		}
		f.row++;
	}
	wattroff(c->win.field, 4);
}

int			print_winner_visual(t_corewar *c)
{
	int			i;
	t_player	*winner;

	i = wgetch(c->win.field);
	winner = get_winner(c);
	if (i == 'q')
	{
		c->pause = 0;
	}
	clear_field(c);
	mvwprintw(c->win.field, 2, 5, "Contestant %p", winner);
	if (winner)
	{
		clear_field(c);
		mvwprintw(c->win.field, 2, 5, "Contestant %s", winner->name);
	}
	return (c->pause);
}
