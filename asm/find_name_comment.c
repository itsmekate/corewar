/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 13:26:51 by etugoluk          #+#    #+#             */
/*   Updated: 2018/08/27 13:26:52 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			find_lapki(t_lst **list, int *i, char **new, int arg)
{
	int tmp;

	tmp = ++(*i);
	while ((*list)->str[*i] != '"')
	{
		(*i)++;
		if (!(*list)->str[*i])
		{
			if (!(*new = copy_n(*new, (*list)->str + tmp, *i - tmp, arg)))
			{
				free(new);
				return (-1);
			}
			tmp = 0;
			*i = 0;
			lst_next(list);
			if (!(*list))
			{
				free(new);
				return (-1);
			}
		}
	}
	// printf("lapki %c %d\n", (*list)->str[*i], (*list)->n_str);
	return (tmp);
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

char		*get_name(t_lst **l, int arg, char *new)
{
	int		tmp;
	int		i;

	i = arg;
	// ft_printf("%s %d\n", (*l)->str, (*l)->n_str);
	while (SPACES)
		i++;
	if (!(*l)->str[i] || (*l)->str[i] != '"')
		return (NULL);
	if ((tmp = find_lapki(l, &i, &new, arg)) == -1)
		return (NULL);
	if (!(new = copy_n(new, (*l)->str + tmp, i - tmp, arg)))
	{
		free(new);
		return (NULL);
	}
	i++;
	while (SPACES)
		i++;
	if ((*l)->str[i] > 31 && (*l)->str[i] != '#' && (*l)->str[i] != ';')
	{
		free(new);
		return (NULL);
	}
	// ft_printf("%s %d\n", (*l)->str, (*l)->n_str);
	return (new);
}
