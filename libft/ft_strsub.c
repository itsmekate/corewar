/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:01:59 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/06 17:13:36 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	int		i;

	if (s == NULL)
		return (NULL);
	newstr = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (newstr == NULL)
		return (NULL);
	while (s[start] && len)
	{
		newstr[i] = s[start];
		start++;
		i++;
		len--;
	}
	newstr[i] = '\0';
	return (newstr);
}
