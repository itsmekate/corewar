/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:53:20 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/27 16:53:22 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*find_label(t_lst **list)
{
	char	*label;
	int		i;
	int		j;

	i = 0;
	j = 0;
	label = NULL;
	while ((*list)->str[i] == ' ' || (*list)->str[i] == '\t')
		i++;
	j = i;
	if (!ft_strchr(LABEL_CHARS, (*list)->str[i])
		|| !ft_strchr((*list)->str, ':'))
		return (label);
	while ((*list)->str[i] && (*list)->str[i] != ':' &&
		(*list)->str[i] != ' ' && (*list)->str[i] != '\t')
	{
		if (!ft_strchr(LABEL_CHARS, (*list)->str[i]))
			return (label);
		i++;
	}
	if (!(*list)->str[i] || (*list)->str[i] != ':')
		return (label);
	label = ft_strnew(i - j);
	label = ft_strncpy(label, (*list)->str + j, i - j);
	return (label);
}

int			find_command_number(char *name, t_asm *a)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(name, a->op_tab[i].name))
			return (i + 1);
		i++;
	}
	return (0);
}

int			find_command_name_1(t_lst **list, int i, int size, t_asm *a)
{
	int		j;
	char	*tmp;
	char	*name;
	int		n;

	n = 0;
	j = i;
	while ((*list)->str[i] && ft_strchr(LABEL_CHARS, (*list)->str[i]))
	{
		size++;
		i++;
	}
	if ((*list)->str[i] == ':')
		return (-1);
	name = ft_strnew(size);
	name = ft_strncpy(name, (*list)->str + j, size);
	n = find_command_number(name, a);
	tmp = (*list)->str;
	(*list)->str = ft_strdup((*list)->str + i);
	free(tmp);
	free(name);
	return (n);
}

int			find_command_name(t_lst **list, char *label, t_asm *a)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while ((*list)->str[i] == ' ' || (*list)->str[i] == '\t')
		i++;
	if (label)
		i += ft_strlen(label) + 1;
	while (!ft_strchr(LABEL_CHARS, (*list)->str[i]))
	{
		if (!(*list)->str[i] || (*list)->str[i] == ':')
			return (-1);
		i++;
	}
	return (find_command_name_1(list, i, size, a));
}

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

int			find_comma(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ') || (str[i] == '\t'))
			i++;
		else if (str[i] == '#' || str[i] == ';')
			return (0);
		else if (str[i] == ',')
		{
			j = i + 1;
			while (str[j] && str[j] != '%' && str[j] != 'r' && str[j] != ':'
				&& str[j] != '#' && str[j] != ';' && !ft_isdigit(str[j]))
				j++;
			if (!str[j] || str[j] == '#' || str[j] == ';')
				return (-1);
			else
				return (i + 1);
		}
		else
			return (-1);
	}
	return (i);
}
