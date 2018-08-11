/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:55:57 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/03 16:55:58 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		validation(t_lst **list, t_asm *a)
{
	if (!validation_name(list, a))
		exit(0);
	get_t_op(a);
	validation_commands(list, a);
	return (0);
}
