/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:03:45 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/04 19:44:53 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*n_src;
	unsigned char		*n_dst;

	n_src = (unsigned char*)src;
	n_dst = (unsigned char*)dst;
	while (n)
	{
		if ((unsigned char)c == (*n_dst++ = *n_src++))
		{
			return (n_dst);
		}
		n--;
	}
	return (NULL);
}
