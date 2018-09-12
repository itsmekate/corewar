/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:35:11 by kprasol           #+#    #+#             */
/*   Updated: 2018/09/11 16:35:12 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static	void	print_new(t_corewar *c, t_window win, int i, t_field f)
{
	init_pair(c->map[i].player->number + 10,
		get_color(c->map[i].player->number), COLOR_BLACK);
	wattron(win.field, COLOR_PAIR(c->map[i].player->number + 10));
	wattron(win.field, A_BOLD);
	mvwprintw(win.field, f.row, f.col, "%02x ", c->map[i].value & 0xff);
	wattroff(win.field, A_BOLD);
	wattroff(win.field, COLOR_PAIR(c->map[i].player->number + 10));
}

static	void	print_carriage(t_corewar *c, t_window win, int i, t_field f)
{
	init_pair(c->map[i].player->number + 15, COLOR_BLACK,
		get_color(c->map[i].player->number));
	wattron(win.field, COLOR_PAIR(c->map[i].player->number + 15));
	mvwprintw(win.field, f.row, f.col, "%02x", c->map[i].value & 0xff);
	wattroff(win.field, COLOR_PAIR(c->map[i].player->number + 15));
	mvwprintw(win.field, f.row, f.col + 2, " ");
}

static	void	print_carriage_empty(t_corewar *c, t_window win, int i, t_field f)
{
	init_pair(c->map[i].player->number + 15, COLOR_BLACK,
		COLOR_WHITE);
	wattron(win.field, COLOR_PAIR(c->map[i].player->number + 15));
	mvwprintw(win.field, f.row, f.col, "%02x", c->map[i].value & 0xff);
	wattroff(win.field, COLOR_PAIR(c->map[i].player->number + 15));
	mvwprintw(win.field, f.row, f.col + 2, " ");
}

static	void	print_old(t_corewar *c, t_window win, int i, t_field f)
{
	init_pair(c->map[i].player->number + 10,
		get_color(c->map[i].player->number), COLOR_BLACK);
	wattron(win.field, COLOR_PAIR(c->map[i].player->number + 10));
	mvwprintw(win.field, f.row, f.col, "%02x ", c->map[i].value & 0xff);
	wattroff(win.field, COLOR_PAIR(c->map[i].player->number + 10));
}

void			print_field(t_corewar *c, t_window win)
{
	t_field f;
	int		i;

	i = 0;
	f.col = 2;
	f.row = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			f.row++;
			f.col = 2;
		}
		if (c->map[i].player != NULL && c->map[i].is_new != 0
			&& c->map[i].process == NULL)
			print_new(c, win, i, f);
		else if (c->map[i].player != NULL && c->map[i].process != NULL)
			print_carriage(c, win, i, f);
		else if (c->map[i].player == NULL && c->map[i].process != NULL)
			print_carriage_empty(c, win, i, f);
		else if (c->map[i].player != NULL)
			print_old(c, win, i, f);
		else
			mvwprintw(win.field, f.row, f.col, "%02x ", c->map[i].value & 0xff);
		i++;
		f.col += 3;
	}
}

int				print_players(t_corewar *c, t_window win)
{
	int i;
	int row;

	i = 0;
	row = 10;
	while (i < c->players_num)
	{
		init_pair(c->players[i]->number + 10,
			get_color(c->players[i]->number), COLOR_BLACK);
		mvwprintw(win.score, row, 3, "Player -%d :", c->players[i]->number);
		wattron(win.score, COLOR_PAIR(c->players[i]->number + 10));
		mvwprintw(win.score, row, 15, "%s", c->players[i]->name);
		wattroff(win.score, COLOR_PAIR(c->players[i]->number + 10));
		mvwprintw(win.score, row + 1, 4, "%s", "Last live:");
		mvwprintw(win.score, row + 2, 4, "%s", "Lives in current period :");
		row += 5;
		i++;
	}
	return (row);
}
