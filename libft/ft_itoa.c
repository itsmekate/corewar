/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:00:53 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/13 18:34:22 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_size(int n)
{
	int		count;
	int		len;

	count = 0;
	len = n;
	if (n < 0)
		count = 1;
	else if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
		n = -n;
	while (len != 0)
	{
		len /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char		*newstr;
	int			i;
	long int	nb;

	nb = n;
	i = ft_size(nb);
	newstr = (char*)malloc(sizeof(char) * i + 1);
	if (newstr == NULL)
		return (NULL);
	newstr[i--] = '\0';
	if (nb < 0)
	{
		newstr[0] = '-';
		nb = -nb;
	}
	while (nb > 9)
	{
		newstr[i--] = (nb % 10) + 48;
		nb /= 10;
	}
	newstr[i] = nb + 48;
	return (newstr);
}
