/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 17:52:27 by kprasol           #+#    #+#             */
/*   Updated: 2018/09/11 17:52:28 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	draw_borders(t_window win)
{
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	wattron(win.field, COLOR_PAIR(1));
	box(win.field, 0, 0);
	wattroff(win.field, COLOR_PAIR(1));
	wattron(win.score, COLOR_PAIR(1));
	box(win.score, 0, 0);
	wattroff(win.score, COLOR_PAIR(1));
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_BLACK);
}

void			del_all(t_window win)
{
	delwin(win.field);
	delwin(win.score);
	endwin();
}

void			create_win(t_window *win)
{
	int score_size;

	score_size = 70;
	initscr();
	noecho();
	curs_set(FALSE);
	start_color();
	win->h = (MEM_SIZE / 64) + 2;
	win->field = newwin(win->h, 195, 0, 0);
	win->score = newwin(win->h, score_size, 0, 196);
	nodelay(win->field, true);
	nodelay(win->score, true);
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
	else if (i == 32 && c->pause == 1)
		c->pause = 0;
	else if (i == 113)
	{
		del_all(c->win);
		exit(0);
	}
	return (c->pause);
}

int				visualize(t_corewar *c)
{
	draw_borders(c->win);
	print_sidebar(c);
	print_field(c);
	wrefresh(c->win.field);
	wrefresh(c->win.score);
	c->pause = exit_visual(c);
	while (c->pause)
	{
		c->pause = exit_visual(c);
	}
	return (1);
}
