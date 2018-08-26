/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:20:06 by etugoluk          #+#    #+#             */
/*   Updated: 2017/10/30 14:20:08 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_putstr_p(char const *s)
{
	int			i;

	i = 0;
	if (!s)
		return (ft_putstr_p("(null)"));
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int				ft_putstrn(char const *s, int n)
{
	int			i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i] && i < n)
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

void			ft_putnbr_p(intmax_t n)
{
	uintmax_t	i;
	intmax_t	n_copy;
	intmax_t	div;

	div = 0;
	i = 1;
	n_copy = n;
	if (n < 0)
	{
		ft_putchar('-');
		n_copy = -n_copy;
	}
	while ((n_copy / i) > 0)
		i *= 10;
	if (n_copy != 0)
		i /= 10;
	while (i != 0)
	{
		div = n_copy / i;
		ft_putchar(div + 48);
		n_copy %= i;
		i /= 10;
	}
}

void			ft_putnbr1(uintmax_t n)
{
	uintmax_t	i;
	uintmax_t	n_copy;
	uintmax_t	div;

	div = 0;
	i = 1;
	n_copy = n;
	while ((n_copy / i) > 0 && i / 10 < 1000000000000000000)
		i *= 10;
	if (n_copy != 0 && n_copy / 10 < 1000000000000000000)
		i /= 10;
	while (i != 0)
	{
		div = n_copy / i;
		ft_putchar(div + 48);
		n_copy %= i;
		i /= 10;
	}
}
