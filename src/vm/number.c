/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:13:30 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:13:34 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				is_number(char *s)
{
	int		len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if ((len == 10 && *s != '2') || len > 10)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

static int		is_exist(t_corewar *corewar, int num)
{
	int i;

	i = 0;
	while (i < corewar->players_num)
	{
		if (corewar->players[i]->number == num)
			return (1);
		i++;
	}
	return (0);
}

static void		wrong_champ_number(t_corewar *corewar, int num)
{
	num = num == -1 ? 0 : num;
	ft_putstr_fd("ERROR: Wrong champion number: ", 2);
	ft_putnbr_fd(num, 2);
	ft_putstr_fd("\n", 2);
	clear_corewar(&corewar);
	exit(0);
}

int				handle_player_number(char ***argv)
{
	int res;

	res = flag_value_handler(argv);
	return (res ? res : -1);
}

int				get_number(t_corewar *corewar, int num)
{
	int ret;

	if (!num)
	{
		if (!corewar->players_num)
			ret = 1;
		else
		{
			ret = corewar->players[corewar->players_num - 1]->number + 1;
			while (ret <= 0 || is_exist(corewar, ret))
				ret++;
		}
		return (ret);
	}
	ret = num;
	if (is_exist(corewar, ret) || num < 0 || num > 200)
		wrong_champ_number(corewar, num);
	return (ret);
}
