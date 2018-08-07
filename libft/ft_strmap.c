/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:13:18 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/06 17:09:34 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*strnew;
	int		i;
	size_t	len;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	strnew = (char*)malloc(sizeof(char) * (len + 1));
	if (strnew == NULL)
		return (NULL);
	while (s[i])
	{
		if (f(s[i]))
			strnew[i] = f(s[i]);
		i++;
	}
	strnew[i] = '\0';
	return (strnew);
}
