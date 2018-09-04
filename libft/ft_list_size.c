/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:49:48 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/16 15:14:37 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_list_size(t_list *begin_list)
{
	t_list		*current;
	int			counter;

	if (begin_list == NULL)
		return (0);
	counter = 0;
	current = begin_list;
	while (current != NULL)
	{
		current = current->next;
		counter++;
	}
	return (counter);
}
