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

static	void	print_carriage(t_corewar *c, int i, t_field f)
{
	init_pair(c->map[i].player->number + 16, COLOR_BLACK,
		get_color(c->map[i].player->number));
	wattron(c->win.field, COLOR_PAIR(c->map[i].player->number + 16));
	mvwprintw(c->win.field, f.row, f.col, "%02x", c->map[i].value & 0xff);
	wattroff(c->win.field, COLOR_PAIR(c->map[i].player->number + 16));
	mvwprintw(c->win.field, f.row, f.col + 2, " ");
}

static	void	print_carriage_empty(t_corewar *c, int i, t_field f)
{
	wattron(c->win.field, COLOR_PAIR(3));
	mvwprintw(c->win.field, f.row, f.col, "%02x", c->map[i].value & 0xff);
	wattroff(c->win.field, COLOR_PAIR(3));
	mvwprintw(c->win.field, f.row, f.col + 2, " ");
}

static	void	print_old(t_corewar *c, int i, t_field f)
{
	init_pair(c->map[i].player->number + 10,
		get_color(c->map[i].player->number), COLOR_BLACK);
	wattron(c->win.field, COLOR_PAIR(c->map[i].player->number + 10));
	mvwprintw(c->win.field, f.row, f.col, "%02x ", c->map[i].value & 0xff);
	wattroff(c->win.field, COLOR_PAIR(c->map[i].player->number + 10));
}

t_field			print_field2(t_corewar *c, t_field f, int i)
{
	if (i % 64 == 0)
	{
		f.row++;
		f.col = 2;
	}
	if (c->map[i].player != NULL && c->map[i].is_new != 0
		&& c->map[i].process == NULL)
	{
		print_new(c, i, f);
		c->map[i].is_new--;
	}
	else if (c->map[i].player != NULL && c->map[i].process != NULL)
		print_carriage(c, i, f);
	else if (c->map[i].player == NULL && c->map[i].process != NULL)
		print_carriage_empty(c, i, f);
	else if (c->map[i].player != NULL)
		print_old(c, i, f);
	else
		mvwprintw(c->win.field, f.row, f.col,
			"%02x ", c->map[i].value & 0xff);
	return (f);
}

void			print_field(t_corewar *c)
{
	t_field	f;
	int		i;

	i = 0;
	f.col = 2;
	f.row = 0;
	while (i < MEM_SIZE)
	{
		f = print_field2(c, f, i);
		i++;
		f.col += 3;
	}
}
