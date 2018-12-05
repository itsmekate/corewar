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

// void		clear_field(t_corewar *c)
// {
// 	t_field f;

// 	f.col = 1;
// 	f.row = 1;
// 	wattron(c->win.field, 4);
// 	while (f.row <= MEM_SIZE / 64)
// 	{
// 		f.col = 1;
// 		while (f.col < 193)
// 		{
// 			mvwprintw(c->win.field, f.row, f.col, " ");
// 			f.col++;
// 		}
// 		f.row++;
// 	}
// 	wattroff(c->win.field, 4);
// }

int			print_winner_visual(t_corewar *c)
{
	int			i;
	t_player	*winner;
	WINDOW 		*popup;

	popup = newwin(10, 152, 20, 25);
	nodelay(popup, true);
	noecho();
	curs_set(FALSE);
	wattron(popup, COLOR_PAIR(1));
	box(popup, 0, 0);
	wattroff(popup, COLOR_PAIR(1));
	i = wgetch(c->win.field);
	winner = get_winner(c);
	if (i != ERR)
		c->pause = 0;
	if (winner)
		mvwprintw(popup, 2, 5, "Contestant %s won", winner->name);
	else
		mvwprintw(popup, 2, 60, "There are no winners");
	wrefresh(popup);
	delwin(popup);
	return (c->pause);
}

int	print_name(t_corewar *c, int row, int i)
{
	int len;

	len = ft_strlen(c->players[i]->name);
	if ( len > 57 && len < 71)
	{
		mvwprintw(c->win.score, row, 15, "%.40s", c->players[i]->name);
		mvwprintw(c->win.score, row+=1, 15, "%.40s", c->players[i]->name);
		}
	else if (len >= 71)
	{
		mvwprintw(c->win.score, row, 15, "%.57s", c->players[i]->name);
		mvwprintw(c->win.score, row+=1, 16, "%.68s", c->players[i]->name);
		mvwprintw(c->win.score, row+=1, 17, "%.3s", c->players[i]->name);
	}
	else
		mvwprintw(c->win.score, row, 15, "%s", c->players[i]->name);
	return (row);
}