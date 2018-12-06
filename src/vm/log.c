/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzabrots <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:21:13 by dzabrots          #+#    #+#             */
/*   Updated: 2018/12/05 17:21:16 by dzabrots         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			log_cycle_to_die(t_corewar *corewar)
{
	char	*buf;
	char	*number;

	if (corewar->verbal & L_CYCLE && corewar->cycle >= corewar->start)
	{
		number = ft_itoa(corewar->cycle_to_die);
		buf = ft_strjoin("Cycle to die is now ", number);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(buf, ft_strlen(buf) + 1));
		else
			ft_putendl_fd(buf, 1);
		free(buf);
		free(number);
	}
}

void			log_cycle(t_corewar *corewar)
{
	char	*buf;
	char	*number;

	if (corewar->verbal & L_CYCLE && corewar->cycle >= corewar->start)
	{
		number = ft_itoa(corewar->cycle);
		buf = ft_strjoin("It is now cycle ", number);
		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(buf, ft_strlen(buf) + 1));
		else
			ft_putendl_fd(buf, 1);
		free(buf);
		free(number);
	}
}

static char		*add_value(char *str, t_corewar *corewar, t_process *process,
	int move)
{
	char	*buf1;
	char	*buf2;
	char	*number;
	int		i;

	i = -1;
	buf2 = str;
	while (++i < move)
	{
		number = ft_itoa_base(corewar->map[
			get_index(process->position + i)].value & 0xff, 16, 2);
		buf1 = ft_strjoin(buf2, number);
		free(buf2);
		buf2 = ft_strjoin(buf1, " ");
		free(number);
		free(buf1);
	}
	return (buf2);
}

static void		log_log_move(t_corewar *corewar, char *str)
{
	if (corewar->visual_mode)
		ft_lstadd(&corewar->log, ft_lstnew(str, ft_strlen(str) + 1));
	else
		ft_putendl_fd(str, 1);
}

void			log_move(t_corewar *corewar, t_process *process, int move)
{
	char	*buf[3];

	if (corewar->verbal & L_MOVE && corewar->cycle >= corewar->start)
	{
		buf[0] = ft_itoa(move);
		buf[1] = ft_strjoin("ADV ", buf[0]);
		buf[2] = ft_strjoin(buf[1], " (0x");
		free(buf[1]);
		free(buf[0]);
		buf[0] = ft_itoa_base(process->position, 16, 4);
		buf[1] = ft_strjoin(buf[2], buf[0]);
		free(buf[0]);
		free(buf[2]);
		buf[0] = ft_itoa_base(process->position + move, 16, 4);
		buf[2] = ft_strjoin(buf[1], " -> 0x");
		free(buf[1]);
		buf[1] = ft_strjoin(buf[2], buf[0]);
		free(buf[2]);
		free(buf[0]);
		buf[2] = ft_strjoin(buf[1], ") ");
		free(buf[1]);
		buf[1] = add_value(buf[2], corewar, process, move);
		log_log_move(corewar, buf[1]);
		free(buf[1]);
	}
}
