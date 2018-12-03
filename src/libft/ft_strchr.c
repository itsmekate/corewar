/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:10:17 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/04 13:06:04 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	char	*b;

	b = (char*)s;
	a = (char)c;
	if (!b || !a)
		return (NULL);
	while (*b || (*b == a))
	{
		if (*b == a)
			return (b);
		b++;
	}
	return (NULL);
}
