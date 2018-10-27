/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:00:32 by dzabrots          #+#    #+#             */
/*   Updated: 2018/09/23 22:00:34 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm.h"

unsigned int	get_arg(int size, int start_index, t_corewar *corewar)
{
	char			res[4];
	unsigned int	arg;
	int				i;

	ft_memset(res, '\0', 4);
	i = -1;
	while (++i < size)
		res[size - 1 - i] = corewar->map[get_index(start_index + i)].value & 0xff;
	arg = *(unsigned int *)res;
	return (arg);
}

void			set_unsigned_int(unsigned int value, int start_index, t_corewar *corewar, t_player *player)
{
	int i;

	i = 0;

	while (i < 4)
	{
		set_point(&corewar->map[get_index(start_index)], value >> 24, player);
		value = value << 8;
		start_index++;
		i++;
	}
}

int				get_value(unsigned int *arg, t_process *process,
	t_corewar *corewar, int *move)
{
	if (*arg == REG_CODE)
	{
		//printf("REG_CODE\n");
		*arg = get_arg(1, process->position + *move, corewar);
		//printf("%i\n", *arg);
		//printf("r%i\n", *arg);
		*move = *move + 1;
		// if (!*arg && process->command == 0xb)
		// {
		// 	//printf("error\n");
		// 	return (0);
		// }
		if (*arg <= REG_NUMBER && *arg)
		{
			*arg = process->reg[*arg - 1];
			//printf("%08x\n", *arg);
		}
		else
			return (0);
	}
	else if (*arg == DIR_CODE)
	{
		//printf("DIR_CODE\n");
		*arg = get_arg(get_label(process->command), process->position + *move, corewar);
		*move = *move + get_label(process->command);
	}
	else if (*arg == IND_CODE)
	{
		//printf("IND_CODE\n");
		*arg = get_arg(2, process->position + *move, corewar);
		*move = *move + 2;
		*arg = get_arg(4, process->position + (short)*arg % IDX_MOD, corewar);
	}
	return (1);
}

void			error_codage(unsigned int *arg, t_process *process, t_corewar *corewar)
{
	int		move;
	int		i;

	move = 2;
		i = -1;
		while (++i < 3)
		{
			if (arg[i] == REG_CODE)
				move++;
			else if (arg[i] == IND_CODE)
				move += 2;
			else if (arg[i] == DIR_CODE)
				move += get_label(process->command);
		}
		log_move(corewar, process, move);
		move_process(move, process, corewar);
}

void			get_types(unsigned int *arg, t_process *process, t_corewar *corewar)
{
	char			codage;

	codage = get_arg(1, process->position + 1, corewar);
	arg[0] = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg[1] = (codage & 0xff) >> 6;
	codage = codage << 2;
	arg[2] = (codage & 0xff) >> 6;
}
