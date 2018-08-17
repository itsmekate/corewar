/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 16:49:30 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/13 14:35:54 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*newstr;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	len = (int)ft_strlen(s);
	len--;
	while ((s[len] == ' ' || s[len] == '\t' || s[len] == '\n') && s[len])
		len--;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && s[i])
		i++;
	if (len == -1)
		len = i - 1;
	newstr = (char*)malloc(sizeof(char) * (len - (i - 1)) + 1);
	if (newstr == NULL)
		return (NULL);
	while (s[i] && i <= len)
		newstr[j++] = s[i++];
	newstr[j] = '\0';
	return (newstr);
}
