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

void			print_sidebar(t_corewar *c)
{
	if (c->pause == 1)
		mvwprintw(c->win.score, 1, 3, "%s", "** PAUSED  **");
	else
		mvwprintw(c->win.score, 1, 3, "%s", "** RUNNING **");
	mvwprintw(c->win.score, 4, 3, "%s", "Cycles/seconds limit:");
	mvwprintw(c->win.score, 6, 3, "Cycle: %d", c->cycle);
	mvwprintw(c->win.score, 8, 3, "%s", "Processes:");
	c->win.score_row = print_players(c);
	mvwprintw(c->win.score, c->win.score_row += 2, 3,
		"CYCLE_TO_DIE : %d", c->cycle_to_die);
	wattron(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 32, 0, "%s",
		"                                 LOG                                  ");
	wattroff(c->win.score, COLOR_PAIR(3));
	print_visual_log(c);
	wattron(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 7, 0, "%s",
		"                                                                      ");
	wattroff(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 5, 3, "%s", "USE Q TO EXIT");
	mvwprintw(c->win.score, c->win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
}

void	print_visual_log(t_corewar *c)
{
	int i;
	t_list	*tmp;

	i = 0;
	tmp = c->log;
	c->win.score_row = c->win.h - 31;
	if (tmp != NULL)
	{
		while (tmp->next && i++ < 10)
		{
			mvwprintw(c->win.score, c->win.score_row += 2, 3, tmp->content);
			tmp = tmp->next;
		}
	}
	else
		mvwprintw(c->win.score, c->win.score_row += 2, 3, "NO LOG AVALIABLE");
}

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
		wrefresh(c->win.score);
		c->pause = 1;
	}
	else if (i == 32 && c->pause == 1)
		c->pause = 0;
	else if (i == 113)
	{
		del_all(c->win);
		exit (0);
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
