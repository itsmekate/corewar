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

int			str_comment(char *str)
{
	char	*tmp;

	tmp = ft_strsub(str, 0, 8);
	if (!ft_strcmp(tmp, ".comment"))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int			str_name(char *str)
{
	char	*tmp;

	tmp = ft_strsub(str, 0, 5);
	if (!ft_strcmp(tmp, ".name"))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char		*copy_n(char *dst, const char *src, int i, int len, int arg)
{
	int j;

	j = 0;
	if (!dst)
	{
		dst = (arg == 5) ? ft_memalloc(PROG_NAME_LENGTH) : ft_memalloc(COMMENT_LENGTH);
		dst = copy_n(dst, src, i, len, arg);
		return (dst);
	}
	if (arg == 5 && i >= PROG_NAME_LENGTH)
	{
		ft_putendl("Champion name too long (Max length 128)");
		free(dst);
		return (NULL);
	}
	if (arg == 8 && i >= COMMENT_LENGTH)
	{
		ft_putendl("Champion comment too long (Max length 2048)");
		free(dst);
		return (NULL);
	}
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

int			find_lapki(t_lst **list, int *i, char *new, int arg)
{
	int tmp;

	tmp = ++(*i);
	while ((*list)->str[*i] != '"')
	{
		(*i)++;
		if (!(*list)->str[*i])
		{
			if (!(new = copy_n(new, (*list)->str + tmp, ft_strlen(new), *i - tmp, arg)))
			{
				free(new);
				return (-1);
			}
			tmp = 0;
			i = 0;
			lst_next(list);
			if (!(*list))
			{
				free(new);
				return (-1);
			}
		}
	}
	return (tmp);
}

char		*get_name(t_lst **list, int arg)
{
	char	*new;
	int		tmp;
	int		i;

	new = NULL;
	i = arg;
	while (SPACES)
		i++;
	if (!(*list)->str[i] || (*list)->str[i] != '"')
		return (NULL);
	if ((tmp = find_lapki(list, &i, new, arg)) == -1)
		return (NULL);
	if (!(new = copy_n(new, (*list)->str + tmp, ft_strlen(new), i - tmp, arg)))
	{
		free(new);
		return (NULL);
	}
	i++;
	while (SPACES)
		i++;
	if ((*list)->str[i] && (*list)->str[i] != '#' && (*list)->str[i] != ';')
	{
		free(new);
		return (NULL);
	}
	return (new);
}
