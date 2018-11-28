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

void			clear_field(t_corewar *c)
{
	t_field f;

	f.col = 1;
	f.row = 1;
	wattron(c->win.field, 4);
	while (f.row <= MEM_SIZE/64)
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

int			print_winner_visual(t_player *winner, t_corewar *c)
{
	int i;

	i = wgetch(c->win.field);
	if (i == 'q')
	{
		c->pause = 0;
	}
	// if (winner)
	// {
		clear_field(c);
		mvwprintw(c->win.field, 2, 5, "Contestant"/*, winner->number, winner->name*/);
		mvwprintw(c->win.field, 25, 50, " ______     ______     __    __     ______        ______     __   __   ______     ______    ");
		mvwprintw(c->win.field, 26, 50, "/\\  ___\\   /\\  __ \\   /\\ \"-./  \\   /\\  ___\\      /\\  __ \\   /\\ \\ / /  /\\  ___\\   /\\  == \\   ");
		mvwprintw(c->win.field, 27, 50, "\\ \\ \\__ \\  \\ \\  __ \\  \\ \\ \\-./\\ \\  \\ \\  __\\      \\ \\ \\/\\ \\  \\ \\ \'/   \\ \\  __\\   \\ \\  __<   ");
		mvwprintw(c->win.field, 28, 50, " \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\     \\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_\\ \\_\\ ");
		mvwprintw(c->win.field, 29, 50, "  \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      \\/_____/   \\/_/      \\/_____/   \\/_/ /_/ ");
	// }
	return (c->pause);
}