#include "vm.h"

void	print_sidebar(t_corewar *c, t_window win)
{
	if (c->pause == 1)
		mvwprintw(win.score, 1, 3, "%s", "** PAUSED **");
	else
		mvwprintw(win.score, 1, 3, "%s", "** RUNNING **");
	mvwprintw(win.score, 4, 3, "%s", "Cycles/seconds limit:");
	mvwprintw(win.score, 6, 3, "Cycle: %d", c->cycle);
	mvwprintw(win.score, 8, 3, "%s", "Processes:");

	win.score_row = print_players(c, win);

	mvwprintw(win.score, win.score_row += 2, 3, "%s", "Live breakdown for current period :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "[---------------------------------------------]");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "Live breakdown for last period :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "[---------------------------------------------]");
	mvwprintw(win.score, win.score_row += 2, 3, "CYCLE_TO_DIE : %d", c->cycle_to_die);
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "CYCLE_DELTA :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "NBR_LIVE :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "MAX_CHECKS :");

	mvwprintw(win.score, win.h - 5, 3, "%s", "USE Q TO EXIT");
	mvwprintw(win.score, win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
}

static	void	draw_borders(t_window win)
{
	init_pair (1, COLOR_WHITE, COLOR_WHITE);
	wattron(win.field,COLOR_PAIR(1));
	box(win.field, 0, 0);
	wattroff(win.field,COLOR_PAIR(1));

	wattron(win.score,COLOR_PAIR(1));
	box(win.score, 0, 0);
	wattroff(win.score,COLOR_PAIR(1));
}

void		del_all(t_window win)
{
	delwin(win.field);
	delwin(win.score);
	endwin();
}

void		create_win(t_window *win)
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
}

int visualize(t_corewar *c)
{
	t_window win;

	c->pause = 1;
	create_win(&win);
	draw_borders(win);
	print_sidebar(c, win);
	print_field(c, win);
	wrefresh(win.field);
	wrefresh(win.score);
	while(c->pause)
	{
		if (wgetch(win.field) == 32)
		{
			c->pause = 0;
		}
		if (wgetch(win.field) == 113)
		{
			del_all(win);
			return (0);
		}
	}
	return (1);
}