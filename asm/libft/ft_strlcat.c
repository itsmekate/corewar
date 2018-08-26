/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 16:40:03 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/13 20:11:02 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	i = ft_strlen(dst);
	while (src[j] && (dstsize - 1 != i))
	{
		dst[i + j] = src[j];
		j++;
		dstsize--;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
