/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 15:12:58 by kprasol           #+#    #+#             */
/*   Updated: 2018/10/20 15:12:59 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			clear_row(WINDOW *win, int y)
{
	int x;

	x = 1;
	while (x < 60)
	{
		wattron(win, 4);
		mvwprintw(win, y, x, " ");
		wattroff(win, 4);
		x++;
	}
}

void			print_sidebar(t_corewar *c)
{
	if (c->pause == 1)
	{
		mvwprintw(c->win.score, 1, 3, "%s", "** PAUSED  **");
		mvwprintw(c->win.score, c->win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
	}
	else if (c->debug == 1)
		mvwprintw(c->win.score, 1, 15, "%s", "  DEBUG MODE IS ON");
	else
	{
		mvwprintw(c->win.score, 1, 3, "%s", "** RUNNING **");
		mvwprintw(c->win.score, c->win.h - 3, 3,
			"%s", "USE SPACE TO STOP       ");
	}
	mvwprintw(c->win.score, 3, 3, "Cycle: %d", c->cycle);
	mvwprintw(c->win.score, 5, 3, "%s", "Processes:");
	c->win.score_row = print_players(c);
	mvwprintw(c->win.score, c->win.score_row += 1, 3,
		"CYCLE_TO_DIE : %d      ", c->cycle_to_die);
	wattron(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.score_row += 2, 0, "%s%s",
		"                                 LOG",
		"                                  ");
	wattroff(c->win.score, COLOR_PAIR(3));
	print_visual_log(c);
	wattron(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 7, 0, "%s%s",
		"                                   ",
		"                                   ");
	wattroff(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 5, 3, "%s", "USE Q TO EXIT");
	mvwprintw(c->win.score, c->win.h - 4, 3, "%s", "USE D FOR DEBUG MODE");
}

void			print_visual_log(t_corewar *c)
{
	int		i;
	t_list	*tmp;
	int		n;
	int		row;

	i = 0;
	tmp = c->log;
	n = c->win.h - c->win.score_row - 8;
	row = c->win.h - 7;
	if (tmp != NULL)
	{
		while (tmp && i++ < n)
		{
			clear_row(c->win.score, row -= 1);
			if (ft_strcmp(tmp->content, "\n") != 0)
				mvwprintw(c->win.score, row, 3, tmp->content);
			else
				mvwprintw(c->win.score, row, 3, "");
			tmp = tmp->next;
		}
	}
	else
		mvwprintw(c->win.score, c->win.score_row += 2, 3, "NO LOG AVALIABLE");
}

int				print_players(t_corewar *c)
{
	int i;
	int row;

	i = 0;
	row = 7;
	while (i < c->players_num)
	{
		init_pair(c->players[i]->number + 10,
			get_color(c->players[i]->number), COLOR_BLACK);
		mvwprintw(c->win.score, row, 3, "Player -%d :", c->players[i]->number);
		wattron(c->win.score, COLOR_PAIR(c->players[i]->number + 10));
		// mvwprintw(c->win.score, row, 15, "%s", c->players[i]->name);
		row = print_name(c, row, i);
		wattroff(c->win.score, COLOR_PAIR(c->players[i]->number + 10));
		// mvwprintw(c->win.score, row + 1, 4,
		// 	"%s", c->players[i]->comment);
		row += 4;
		i++;
	}
	return (row);
}
