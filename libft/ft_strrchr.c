/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:46:06 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/11 17:22:40 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	str = (char*)s;
	len = ft_strlen(str);
	while (len != -1)
	{
		if (str[len] == (char)c)
			return ((char *)str + (int)len);
		len--;
	}
	return (NULL);
}
