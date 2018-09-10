#include <unistd.h>
#include <menu.h>
#include "vm.h"

typedef struct s_window
{
	WINDOW *field;
	WINDOW *score;
	int 	h;
	int		score_row;
}				t_window;

int print_players(t_corewar *c, t_window win)
{
	int i;
	int row;
	int players;
	int tmp;

	i = 0;
	row = 10;
	players = 0;
	tmp = 0;
	while (players < c->players_num)
	{
		/* NEEDS COLOR TROUBLESHOOTING */
		players++;
		init_pair(c->map[i].player->number + 10, get_color(c->map[i].player->number), COLOR_BLACK);
		mvwprintw(win.score, row, 3, "Player -%d :", c->players[i]->number);
		wattron(win.score, COLOR_PAIR(c->map[i].player->number + 10));
		mvwprintw(win.score, row, 15, "%s", c->players[i]->name);
		wattroff(win.score, COLOR_PAIR(c->map[i].player->number + 10));
		mvwprintw(win.score, row + 1, 4, "%s", "Last live:");
		mvwprintw(win.score, row + 2, 4, "%s", "Lives in current period :");
		row += 5;
		i++;
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
	row = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			row++;
			col = 2;
		}
		/* STILL FIGURING OUT HOW TO MAKE IT WORK FOR NEW PROCESSES*/
		if (c->map[i].player != NULL)
		{
			init_pair (c->map[i].player->number + 10, get_color(c->map[i].player->number), COLOR_BLACK);
			wattron(win.field, COLOR_PAIR(c->map[i].player->number + 10));
			mvwprintw(win.field, row, col, "%02x ", c->map[i].value & 0xff);
			wattroff(win.field, COLOR_PAIR(c->map[i].player->number + 10));
		}
		else
			mvwprintw(win.field, row, col, "%02x ", c->map[i].value & 0xff);
		i++;
		col += 3;
	}
}

void	print_sidebar(t_corewar *c, t_window win)
{
	mvwprintw(win.score, 1, 3, "%s", "** PAUSED **");
	mvwprintw(win.score, 4, 3, "%s", "Cycles/seconds limit:");
	mvwprintw(win.score, 6, 3, "Cycle: %d", c->cycle);
	mvwprintw(win.score, 8, 3, "%s", "Processes:");


	win.score_row = print_players(c, win);
	print_field(c, win);

	mvwprintw(win.score, win.score_row += 2, 3, "%s", "Live breakdown for current period :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "Live breakdown for last period :");
	mvwprintw(win.score, win.score_row += 2, 3, "CYCLE_TO_DIE : %d", c->cycle_to_die);
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "CYCLE_DELTA :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "NBR_LIVE :");
	mvwprintw(win.score, win.score_row += 2, 3, "%s", "MAX_CHECKS :");

	mvwprintw(win.score, win.h - 5, 3, "%s", "USE Q TO EXIT");
	mvwprintw(win.score, win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
}

int visualize(t_corewar *c)
{
	t_window win;
	int parent_x, parent_y;
	int score_size = 70;

	initscr();
	noecho();
	curs_set(FALSE);
	start_color();

	// get our maximum window dimensions
	getmaxyx(stdscr, parent_y, parent_x);

	win.h = (MEM_SIZE / 64) + 2;
	// set up initial windows
	win.field = newwin(win.h, 195, 0, 0);
	win.score = newwin(win.h, score_size, 0, 196);

	init_pair (1, COLOR_WHITE, COLOR_WHITE);
	init_pair (2, COLOR_GREEN, COLOR_BLACK);
	wattron(win.field,COLOR_PAIR(1));
	box(win.field, 0, 0);
	wattroff(win.field,COLOR_PAIR(1));

	wattron(win.score,COLOR_PAIR(1));
	box(win.score, 0, 0);
	wattroff(win.score,COLOR_PAIR(1));

	print_sidebar(c, win);
	// refresh each window
	wrefresh(win.field);
	wrefresh(win.score);
	while (1)
	{
		/* SHOULD RETURN C->PAUSE TO MAIN */
		if (wgetch(win.field) == 32 && c->pause == 0)
			c->pause = 1;
		if (wgetch(win.field) == 32 && c->pause == 1)
			c->pause = 0;
		if (wgetch(win.field) == 113)
	    {
			delwin(win.field);
			delwin(win.score);
			endwin();
			return (0);
		}
	}
}