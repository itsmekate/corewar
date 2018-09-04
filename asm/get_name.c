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
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	tmp = ft_strsub(str, i, 8);
	if (!ft_strcmp(tmp, ".comment"))
	{
		free(tmp);
		return (i + 8);
	}
	free(tmp);
	return (0);
}

int			str_name(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	tmp = ft_strsub(str, i, 5);
	if (!ft_strcmp(tmp, ".name"))
	{
		free(tmp);
		return (i + 5);
	}
	free(tmp);
	return (0);
}

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
	return (tmp);
}

char		*get_name(t_lst **l, int arg, char *new)
{
	int		tmp;
	int		i;

	i = arg;
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
	if ((*l)->str[i] && (*l)->str[i] != '#' && (*l)->str[i] != ';')
	{
		free(new);
		return (NULL);
	}
	return (new);
}
