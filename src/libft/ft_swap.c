/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:59:12 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/17 16:28:23 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	if (*str1 == NULL || str1 == NULL || *str2 == NULL || str2 == NULL)
		return ;
	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}
