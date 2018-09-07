#include <ncurses.h>
#include <unistd.h>
#include <menu.h>
#include "vm.h"

typedef struct s_window
{
	WINDOW *field;
	WINDOW *score;
	// int field_x;
	// int filed_y;
	// int score_x;
	// int score_y;
}				t_window;

int print_players(t_corewar *c, t_window win)
{
	int i;
	int row;

	i = 0;
	row = 10;
	while (i < c->players_num)
	{
		mvwprintw(win.score, row, 3, "Player -%d :", c->players[i]->number);
		wattron(win.score, COLOR_PAIR(2));
		mvwprintw(win.score, row, 15, "%s", c->players[i]->name);
		wattroff(win.score, COLOR_PAIR(2));
		mvwprintw(win.score, row + 1, 4, "%s", "Last live:");
		mvwprintw(win.score, row + 2, 4, "%s", "Lives in current period :");
		i++;
		row += 5;
	}
	return (row);
}

void 	print_field(t_corewar *c, t_window win)
{
	int col;
	int row;
	int i;

	i = 0;
	col = 2;
	row = 1;
	while (i < MEM_SIZE)
	{
		if (col % 64 == 0)
		{
			row++;
			col = 2;
		}
		mvwprintw(win.field, row, col, "%02x ", c->map[i].value & 0xff);
		i++;
		col+=3;
	}
}

int visualize(t_corewar *c)
{
	t_window win;
	int parent_x, parent_y;
	int score_size = 70;
	int score_row;

	initscr();
	noecho();
	curs_set(FALSE);
	start_color();

	// get our maximum window dimensions
	getmaxyx(stdscr, parent_y, parent_x);

	// set up initial windows
	win.field = newwin(129, 129, 0, 0);
	win.score = newwin(129, score_size, 0, 130);

	init_pair (1, COLOR_WHITE, COLOR_WHITE);
	wattron(win.field,COLOR_PAIR(1));
	box(win.field,0,0);
	wattroff(win.field,COLOR_PAIR(1));

	wattron(win.score,COLOR_PAIR(1));
	box(win.score,0,0);
	wattroff(win.score,COLOR_PAIR(1));

	// draw to our windows
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	
	mvwprintw(win.score, 1, 3, "%s", "** PAUSED **");
	mvwprintw(win.score, 4, 3, "%s", "Cycles/seconds limit:");
	mvwprintw(win.score, 6, 3, "%s", "Cycle:");
	mvwprintw(win.score, 8, 3, "%s", "Processes:");


	score_row = print_players(c, win);
	print_field(c, win);

	mvwprintw(win.score, score_row += 2, 3, "%s", "Live breakdown for current period :");
	mvwprintw(win.score, score_row += 2, 3, "%s", "Live breakdown for last period :");
	mvwprintw(win.score, score_row += 2, 3, "CYCLE_TO_DIE : %d", c->cycle_to_die);
	mvwprintw(win.score, score_row += 2, 3, "%s", "CYCLE_DELTA :");
	mvwprintw(win.score, score_row += 2, 3, "%s", "NBR_LIVE :");
	mvwprintw(win.score, score_row += 2, 3, "%s", "MAX_CHECKS :");

	// refresh each window
	wrefresh(win.field);
	wrefresh(win.score);
	while (1)
	{
		if (wgetch(win.field) == 113)
	    {
			delwin(win.field);
			delwin(win.score);
			endwin();
			return (0);
		}
	}
}