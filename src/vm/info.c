/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:27:49 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:27:51 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_cycles(char value)
{
	static int	values[16] = {10, 5, 5, 10,
		10, 6, 6, 6, 20, 25, 25, 800,
		10, 50, 1000, 2};

	value -= 1;
	if (value < 0 || value > 15)
		return (1);
	return (values[(int)(value & 0xff)]);
}

void		init_commands(t_corewar *corewar)
{
	corewar->f[0] = &live;
	corewar->f[1] = &load;
	corewar->f[2] = &store;
	corewar->f[3] = &addition;
	corewar->f[4] = &substraction;
	corewar->f[5] = &ft_and;
	corewar->f[6] = &ft_or;
	corewar->f[7] = &ft_xor;
	corewar->f[8] = &zjump;
	corewar->f[9] = &load_index;
	corewar->f[10] = &store_index;
	corewar->f[11] = &ft_fork;
	corewar->f[12] = &long_load;
	corewar->f[13] = &long_load_index;
	corewar->f[14] = &long_fork;
	corewar->f[15] = &aff;
}

int			get_label(char value)
{
	static int	values[16] = {4, 4, 4, 4,
		4, 4, 4, 4, 2, 2, 2, 2,
		4, 2, 2, 4};

	value -= 1;
	if (value < 0 || value > 15)
		return (0);
	return (values[(int)(value & 0xff)]);
}
