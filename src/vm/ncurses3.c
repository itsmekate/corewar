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

void			print_new(t_corewar *c, int i, t_field f)
{
	init_pair(c->map[i].player->number + 10,
		get_color(c->map[i].player->number), COLOR_BLACK);
	wattron(c->win.field, COLOR_PAIR(c->map[i].player->number + 10));
	wattron(c->win.field, A_BOLD);
	mvwprintw(c->win.field, f.row, f.col, "%02x ", c->map[i].value & 0xff);
	wattroff(c->win.field, A_BOLD);
	wattroff(c->win.field, COLOR_PAIR(c->map[i].player->number + 10));
}

void			print_sidebar2(t_corewar *c)
{
	print_visual_log(c);
	wattron(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 7, 0, "%s%s",
		"                                   ",
		"                                   ");
	wattroff(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.h - 5, 3, "%s", "USE Q TO EXIT");
	mvwprintw(c->win.score, c->win.h - 4, 3, "%s", "USE D FOR DEBUG MODE");
}

void			print_sidebar(t_corewar *c)
{
	if (c->debug == 1)
		mvwprintw(c->win.score, 1, 15, "%s", "  DEBUG MODE IS ON");
	else
		mvwprintw(c->win.score, 1, 15, "%s", "                  ");
	if (c->pause == 1)
	{
		mvwprintw(c->win.score, 1, 3, "%s", "** PAUSED  **");
		mvwprintw(c->win.score, c->win.h - 3, 3, "%s", "USE SPACE TO CONTINUE");
	}
	else
	{
		mvwprintw(c->win.score, 1, 3, "%s", "** RUNNING **");
		mvwprintw(c->win.score, c->win.h - 3, 3,
			"%s", "USE SPACE TO STOP       ");
	}
	mvwprintw(c->win.score, 3, 3, "Cycle: %d", c->cycle);
	c->win.score_row = print_players(c);
	mvwprintw(c->win.score, c->win.score_row += 1, 3,
		"CYCLE_TO_DIE : %d      ", c->cycle_to_die);
	wattron(c->win.score, COLOR_PAIR(3));
	mvwprintw(c->win.score, c->win.score_row += 2, 0, "%s%s",
		"                                 LOG",
		"                                  ");
	wattroff(c->win.score, COLOR_PAIR(3));
	print_sidebar2(c);
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
		clear_row(c->win.score, c->win.score_row += 2);
		while (tmp && i++ < n)
		{
			clear_row(c->win.score, row -= 1);
			print_log_row(c, tmp->content, row);
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
	int len;

	i = 0;
	row = 5;
	while (i < c->players_num)
	{
		init_pair(c->players[i]->number + 10,
			get_color(c->players[i]->number), COLOR_BLACK);
		mvwprintw(c->win.score, row, 3, "Player -%d ", c->players[i]->number);
		wattron(c->win.score, COLOR_PAIR(c->players[i]->number + 10));
		len = ft_strlen(c->players[i]->name);
		row = print_max(c, row, c->players[i]->name, len);
		wattroff(c->win.score, COLOR_PAIR(c->players[i]->number + 10));
		row++;
		len = ft_strlen(c->players[i]->comment);
		row = print_max(c, row, c->players[i]->comment, len);
		row += 2;
		i++;
	}
	return (row);
}
