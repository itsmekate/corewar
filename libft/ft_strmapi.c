/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:37:23 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/06 17:11:03 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	int		i;
	char	*strnew;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char*)s;
	len = ft_strlen(str);
	strnew = (char*)malloc(sizeof(char) * (len + 1));
	if (strnew == NULL)
		return (NULL);
	while (str[i])
	{
		if (f(i, str[i]))
			strnew[i] = f(i, str[i]);
		i++;
	}
	strnew[i] = '\0';
	return (strnew);
}
