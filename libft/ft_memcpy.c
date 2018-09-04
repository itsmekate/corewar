/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:49:04 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/02 16:14:58 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*holder1;
	unsigned char	*holder2;

	holder1 = (unsigned char*)src;
	holder2 = (unsigned char*)dst;
	while (n)
	{
		*holder2++ = *holder1++;
		n--;
	}
	return (dst);
}
