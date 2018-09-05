#include <ncurses.h>
#include <unistd.h>
#include <menu.h>

void draw_borders(WINDOW *screen);

int main(int argc, char **argv)
{
	int parent_x, parent_y;
	int score_size = 70;

	initscr();
	noecho();
	curs_set(FALSE);
	start_color();

	// get our maximum window dimensions
	getmaxyx(stdscr, parent_y, parent_x);

	// set up initial windows
	WINDOW *field = newwin(parent_y, parent_x - score_size, 0, 0);
	WINDOW *score = newwin(parent_y, score_size, 0, parent_x - score_size);

	init_pair (1, COLOR_WHITE, COLOR_WHITE);
	wattron(field,COLOR_PAIR(1));
	box(field,0,0);
	wattroff(field,COLOR_PAIR(1));

	wattron(score,COLOR_PAIR(1));
	box(score,0,0);
	wattroff(score,COLOR_PAIR(1));

	// // Celebration Funbere v0.99pl42

	// draw to our windows

	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	
	mvwprintw(field, 1, 1, "%s", "Field");
	mvwprintw(score, 1, 3, "%s", "** PAUSED **");
	mvwprintw(score, 4, 3, "%s", "Cycles/seconds limit:");
	mvwprintw(score, 6, 3, "%s", "Cycle:");
	mvwprintw(score, 8, 3, "%s", "Processes:");

	mvwprintw(score, 10, 3, "%s", "Player -1 :");
	wattron(score, COLOR_PAIR(2));
	mvwprintw(score, 10, 15, "%s", "Celebration Funbere v0.99pl42");
	wattroff(score, COLOR_PAIR(2));
	mvwprintw(score, 11, 4, "%s", "Last live:");
	mvwprintw(score, 12, 4, "%s", "Lives in current period :");

	mvwprintw(score, 14, 3, "%s", "Player -2 :");
	wattron(score, COLOR_PAIR(2));
	mvwprintw(score, 14, 15, "%s", "Celebration Funbere v0.99pl42");
	wattroff(score, COLOR_PAIR(2));
	mvwprintw(score, 15, 4, "%s", "Last live:");
	mvwprintw(score, 16, 4, "%s", "Lives in current period :");

	mvwprintw(score, 18, 3, "%s", "Live breakdown for current period :");

	mvwprintw(score, 20, 3, "%s", "Live breakdown for last period :");

	mvwprintw(score, 22, 3, "%s", "CYCLE_TO_DIE :");
	mvwprintw(score, 24, 3, "%s", "CYCLE_DELTA :");
	mvwprintw(score, 26, 3, "%s", "NBR_LIVE :");
	mvwprintw(score, 26, 3, "%s", "MAX_CHECKS :");

	// refresh each window

	wrefresh(field);
	wrefresh(score);
	while (1)
	{
		if (wgetch(field) == 113)
	    {
			delwin(field);
			delwin(score);
			endwin();
			return (0);
		}
	}
}

// void draw_borders(WINDOW *screen)
// {
// 	int x, y, i;
// 	getmaxyx(screen, y, x);
// 	// 4 corners
// 	mvwprintw(screen, 0, 0, "+");
// 	mvwprintw(screen, y - 1, 0, "+");
// 	mvwprintw(screen, 0, x - 1, "+");
// 	mvwprintw(screen, y - 1, x - 1, "+");
// 	// sides
// 	for (i = 1; i < (y - 1); i++)
// 	{
// 		mvwprintw(screen, i, 0, "|");
// 		mvwprintw(screen, i, x - 1, "|");
// 	}
// 	// top and bottom
// 	for (i = 1; i < (x - 1); i++)
// 	{
// 		mvwprintw(screen, 0, i, "-");
// 		mvwprintw(screen, y - 1, i, "-");
// 	}
// }