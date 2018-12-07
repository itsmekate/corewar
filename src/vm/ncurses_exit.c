/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:51:10 by kprasol           #+#    #+#             */
/*   Updated: 2018/12/07 12:51:12 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			del_visual(t_window win)
{
	delwin(win.popup);
	delwin(win.field);
	delwin(win.score);
	endwin();
}

void			exit_visual2(t_corewar *c)
{
	if (c->debug)
	{
		c->debug = 0;
		visualize(c);
	}
	else
	{
		c->debug = 1;
		visualize(c);
	}
}

int				exit_visual(t_corewar *c)
{
	int i;

	i = wgetch(c->win.field);
	if (i == 32 && c->pause == 0)
	{
		mvwprintw(c->win.score, 1, 3, "%s", "** PAUSED  **");
		mvwprintw(c->win.score, c->win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
		wrefresh(c->win.score);
		c->pause = 1;
	}
	else if (i == 'd')
		exit_visual2(c);
	else if (i == 32 && c->pause)
		c->pause = 0;
	else if (i == 113)
	{
		del_visual(c->win);
		exit(0);
	}
	return (c->pause);
}

void			clear_row(WINDOW *win, int y)
{
	int x;

	x = 1;
	while (x < 66)
	{
		wattron(win, 4);
		mvwprintw(win, y, x, " ");
		wattroff(win, 4);
		x++;
	}
}
