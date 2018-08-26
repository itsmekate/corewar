/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:56:17 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/16 15:08:42 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_clear(t_list **begin_list)
{
	t_list *next;

	if (*begin_list == NULL || begin_list == NULL)
		return ;
	while (*begin_list != NULL)
	{
		next = *begin_list;
		*begin_list = (*begin_list)->next;
		free(next);
	}
	*begin_list = NULL;
}
