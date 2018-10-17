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

void			print_sidebar(t_corewar *c, t_window win)
{
	if (c->pause == 1)
		mvwprintw(win.score, 1, 3, "%s", "** PAUSED  **");
	else
		mvwprintw(win.score, 1, 3, "%s", "** RUNNING **");
	mvwprintw(win.score, 4, 3, "%s", "Cycles/seconds limit:");
	mvwprintw(win.score, 6, 3, "Cycle: %d", c->cycle);
	mvwprintw(win.score, 8, 3, "%s", "Processes:");
	win.score_row = print_players(c, win);
	// mvwprintw(win.score, win.score_row += 2, 3, "%s",
	// 	"Live breakdown for current period :");
	// mvwprintw(win.score, win.score_row += 2, 3, "%s",
	// 	"[---------------------------------------------]");
	// mvwprintw(win.score, win.score_row += 2, 3, "%s",
	// 	"Live breakdown for last period :");
	// mvwprintw(win.score, win.score_row += 2, 3, "%s",
	// 	"[---------------------------------------------]");
	mvwprintw(win.score, win.score_row += 2, 3,
		"CYCLE_TO_DIE : %d", c->cycle_to_die);
	wattron(win.score, COLOR_PAIR(3));
	mvwprintw(win.score, win.score_row += 2, 0, "%s",
		"                                 LOG                                  ");
	wattroff(win.score, COLOR_PAIR(3));
	print_visual_log(c, win);
	// mvwprintw(win.score, win.score_row += 2, 3, "%s", "CYCLE_DELTA :");
	// mvwprintw(win.score, win.score_row += 2, 3, "%s", "NBR_LIVE :");
	// mvwprintw(win.score, win.score_row += 2, 3, "%s", "MAX_CHECKS :");
	wattron(win.score, COLOR_PAIR(3));
	mvwprintw(win.score, win.h - 7, 0, "%s",
		"                                                                      ");
	wattroff(win.score, COLOR_PAIR(3));
	mvwprintw(win.score, win.h - 5, 3, "%s", "USE Q TO EXIT");
	mvwprintw(win.score, win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
}

void	print_visual_log(t_corewar *c, t_window win)
{
	int i;
	t_list	*tmp;

	i = 0;
	tmp = c->log;
	if (tmp != NULL)
	{
		while (tmp->next && i++ < 10)
		{
			mvwprintw(win.score, win.score_row += 2, 3, tmp->content);
			tmp = tmp->next;
		}
	}
	else
		mvwprintw(win.score, win.score_row += 2, 3, "NO LOG AVALIABLE");
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

int				exit_visual(t_corewar *c, t_window win)
{
	int i;

	i = wgetch(win.field);
	if (i == 32 && c->pause == 0)
	{
		mvwprintw(win.score, 1, 3, "%s", "** PAUSED  **");
		wrefresh(c->win.score);
		c->pause = 1;
	}
	else if (i == 32 && c->pause == 1)
		c->pause = 0;
	else if (i == 113)
	{
		del_all(win);
		exit (0);
	}
	return (c->pause);
}

int				visualize(t_corewar *c)
{
	create_win(&c->win);
	draw_borders(c->win);
	print_sidebar(c, c->win);
	print_field(c, c->win);
	wrefresh(c->win.field);
	wrefresh(c->win.score);
	c->pause = exit_visual(c, c->win);
	while (c->pause)
	{
		c->pause = exit_visual(c, c->win);
	}
	return (1);
}
