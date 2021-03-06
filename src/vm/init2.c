/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:27:04 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:27:06 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				flag_value_handler(char ***argv)
{
	char	**buf;
	int		res;

	buf = *argv;
	if (is_number(*(buf + 1)))
	{
		res = ft_atoi(*(buf + 1));
		if (res >= 0)
		{
			*argv = *argv + 1;
			return (res);
		}
		else
			return (-1);
	}
	return (-1);
}

void			flag_handler(int flag, char ***agrv, t_corewar *res)
{
	if (flag == 2)
		res->dump = flag_value_handler(agrv);
	else if (flag == 3)
		res->verbal = flag_value_handler(agrv);
	else if (flag == 4)
		res->start = flag_value_handler(agrv);
	else if (flag == 5)
		res->visual_mode = 1;
	else if (flag == 6)
		res->debug = 1;
	if (res->dump < 0 || res->verbal < 0 || res->start < 0)
	{
		ft_putstr_fd("ERROR: Wrong flag value\n", 2);
		clear_corewar(&res);
		exit(0);
	}
}
