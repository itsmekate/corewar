/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:42:54 by etugoluk          #+#    #+#             */
/*   Updated: 2018/02/24 13:42:54 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						dig_p(intmax_t n, int k)
{
	int					size;
	intmax_t			i;

	size = 1;
	i = 1;
	if (n / 10 == -922337203685477580 && n % 10 == -8 && k == 0)
		return (20);
	else if (n / 10 == -922337203685477580 && n % 10 == -8 && k == 1)
		return (19);
	if (n < 0 && k == 0)
	{
		size++;
		n = -n;
	}
	else if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

int						digitsu(uintmax_t n)
{
	int					size;
	uintmax_t			i;

	size = 1;
	i = 1;
	if (n / 10 >= 1000000000000000000)
		return (20);
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}
