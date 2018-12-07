/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:34:01 by kprasol           #+#    #+#             */
/*   Updated: 2018/11/26 15:34:18 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		print_winner_visual(t_corewar *c)
{
	int			i;
	t_player	*winner;

	wattron(c->win.popup, COLOR_PAIR(1));
	box(c->win.popup, 0, 0);
	wattroff(c->win.popup, COLOR_PAIR(1));
	i = wgetch(c->win.field);
	winner = get_winner(c);
	if (i != ERR)
		c->pause = 0;
	if (winner)
		mvwprintw(c->win.popup, 2, 5, "Contestant %s won", winner->name);
	else
		mvwprintw(c->win.popup, 2, 60, "There are no winners");
	wrefresh(c->win.popup);
	return (c->pause);
}

int		print_x_chars(t_corewar *c, char *str, int row, t_field f)
{
	int col;
	int start;
	int to;

	col = 15;
	to = f.row;
	start = f.col;
	if (!str)
		return (0);
	while (str[start] && start <= to)
	{
		mvwprintw(c->win.score, row, col, "%c", str[start]);
		col++;
		start++;
	}
	return (start);
}

int		print_max(t_corewar *c, int row, char *str, int len)
{
	t_field	f;

	f.col = 0;
	f.row = 52;
	if (len > 52 && len < 104)
	{
		f.col = print_x_chars(c, str, row, f);
		row++;
		f.row = 104;
		print_x_chars(c, str, row, f);
	}
	else if (len >= 104)
	{
		f.col = print_x_chars(c, str, row, f);
		row++;
		f.row = 105;
		f.col = print_x_chars(c, str, row, f);
		row++;
		f.row = 128;
		print_x_chars(c, str, row, f);
	}
	else
		mvwprintw(c->win.score, row, 15, "%s", str);
	return (row);
}

void	print_log_row(t_corewar *c, char *str, int row)
{
	int col;
	int j;

	col = 3;
	j = 0;
	if (!str)
		return ;
	while (str[j] && j <= 64)
	{
		if (str[j] != '\n')
			mvwprintw(c->win.score, row, col, "%c", str[j]);
		else
			mvwprintw(c->win.score, row, col, "%c", " ");
		col++;
		j++;
	}
}
