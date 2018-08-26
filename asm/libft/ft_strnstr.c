/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 17:35:35 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/11 17:22:55 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;

	n_len = ft_strlen(needle);
	if (n_len == 0)
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (*haystack == *needle &&
				(ft_strncmp(haystack, needle, n_len) == 0))
		{
			if (n_len > len)
				return (NULL);
			return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
