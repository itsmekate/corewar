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
		if ((*list)->str[*i] != 0 && (*list)->str[*i] != 10)
			(*i)++;
		if (!(*list)->str[*i] || (*list)->str[*i] == 10)
		{
			*new = copy_n(*new, (*list)->str + tmp, *i - tmp, arg);
			tmp = 0;
			*i = 0;
			lst_next(list);
			if (!(*list))
			{
				ft_printf("Error: no end of name/comment\n");
				exit(0);
			}
		}
	}
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
		dst = (arg == 1) ? ft_memalloc(PROG_NAME_LENGTH) :
		ft_memalloc(COMMENT_LENGTH);
		dst = copy_n(dst, src, len, arg);
		return (dst);
	}
	if (arg == 1 && (i + len > PROG_NAME_LENGTH))
	{
		ft_putendl("Champion name too long (Max length 128)");
		exit(0);
	}
	if (arg == 2 && (i + len > COMMENT_LENGTH))
	{
		ft_putendl("Champion comment too long (Max length 2048)");
		exit(0);
	}
	return (copy_n1(dst, src, i, len));
}

char		*get_name(t_lst **l, int arg, char *new, int p)
{
	int		tmp;
	int		i;

	i = arg;
	while (SPACES)
		i++;
	if (!(*l)->str[i] || (*l)->str[i] != '"')
		return (NULL);
	if ((tmp = find_lapki(l, &i, &new, p)) == -1)
		return (NULL);
	new = copy_n(new, (*l)->str + tmp, i - tmp, p);
	i++;
	while (SPACES)
		i++;
	if ((*l)->str[i] > 31 && (*l)->str[i] != '#' && (*l)->str[i] != ';')
	{
		free(new);
		return (NULL);
	}
	return (new);
}
