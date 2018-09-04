/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:45:25 by etugoluk          #+#    #+#             */
/*   Updated: 2018/09/04 17:45:26 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*get_arg_label(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] && str[i] != ',' && str[i] != ' ' && str[i] != '\t')
		i++;
	if (!i)
		return (NULL);
	new = ft_strsub(str, 0, i);
	return (new);
}

int			count_codage(t_args t)
{
	int		i;
	int		codage;

	i = 0;
	codage = 0;
	while (t.arg_arr[i].type && i < 3)
	{
		if (t.arg_arr[i].type == 1)
			codage += ft_pow(2, 6 - i * 2);
		else if (t.arg_arr[i].type == 2)
			codage += ft_pow(2, 7 - i * 2);
		else if (t.arg_arr[i].type == 3)
			codage += ft_pow(2, 7 - i * 2) + ft_pow(2, 6 - i * 2);
		i++;
	}
	return (codage);
}

char		*copy_n1(char *dst, const char *src, int i, int len)
{
	int		j;

	j = 0;
	while (j < len && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (!src[j])
		dst[i] = '\n';
	return (dst);
}

char		*copy_n(char *dst, const char *src, int len, int arg)
{
	int		i;

	i = ft_strlen(dst);
	if (!dst)
	{
		dst = (arg == 5) ? ft_memalloc(PROG_NAME_LENGTH) :
		ft_memalloc(COMMENT_LENGTH);
		dst = copy_n(dst, src, len, arg);
		return (dst);
	}
	if (arg == 5 && len >= PROG_NAME_LENGTH)
	{
		ft_putendl("Champion name too long (Max length 128)");
		free(dst);
		return (NULL);
	}
	if (arg == 8 && len >= COMMENT_LENGTH)
	{
		ft_putendl("Champion comment too long (Max length 2048)");
		free(dst);
		return (NULL);
	}
	return (copy_n1(dst, src, i, len));
}
