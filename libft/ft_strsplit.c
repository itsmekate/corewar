/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:08:36 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/13 19:23:43 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_create(char const *s, int start, int end)
{
	char	*str;
	int		divi;
	int		i;

	i = 0;
	divi = end - start;
	str = (char *)malloc(sizeof(char) * (divi) + 1);
	if (str == NULL)
		return (NULL);
	while (divi--)
	{
		str[i] = s[start++];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static	int		ft_wcount(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] && s[i] == c)
			i++;
		else if (s[i] != c)
		{
			i++;
			if (s[i] == c || s[i] == '\0')
				counter++;
		}
	}
	return (counter);
}

static	void	ft_splitter(char const *s, char c, int wnum, char **arr)
{
	int		i;
	int		start;
	int		end;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && j < wnum)
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			end = i;
			arr[j] = ft_create(s, start, end);
			if (arr[j] == NULL)
				return ;
			j++;
		}
		i++;
	}
	arr[j] = 0;
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		wnum;

	if (s == NULL)
		return (NULL);
	wnum = ft_wcount(s, c);
	arr = (char**)malloc(sizeof(char*) * (wnum + 1));
	if (!arr)
		return (NULL);
	ft_splitter(s, c, wnum, arr);
	return (arr);
}
