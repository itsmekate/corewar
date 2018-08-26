/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 18:09:42 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/02 19:44:17 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;
	int		count;

	count = -1;
	len = ft_strlen(s1);
	s2 = (char*)malloc(sizeof(char) * len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[++count])
		s2[count] = s1[count];
	s2[count] = '\0';
	return (s2);
}
