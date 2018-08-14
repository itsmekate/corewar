/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:26:33 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/16 16:15:07 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	a = (unsigned char*)src;
	b = (unsigned char*)dst;
	if (src < dst)
	{
		i = len;
		while (i--)
			b[i] = a[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			b[i] = a[i];
			i++;
		}
	}
	return (dst);
}
