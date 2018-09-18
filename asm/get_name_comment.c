/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:17:10 by kprasol           #+#    #+#             */
/*   Updated: 2018/08/02 15:17:12 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_command(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue;
		}
		if (str[i] == '#' || str[i] == ';')
			return (0);
		else
			return (1);
	}
	return (0);
}

int			set_bot_name(t_asm *a, char *tmp_buf_name, int *name_exists)
{
	if (!tmp_buf_name)
	{
		ft_putendl("Syntax error: incorrect name");
		return (0);
	}
	if (*name_exists > 0)
	{
		ft_strdel(&tmp_buf_name);
		ft_putendl("Lexical error: incorrect number of name statements");
		return (0);
	}
	if (!a->bot_name)
		a->bot_name = tmp_buf_name;
	(*name_exists)++;
	return (1);
}

int			set_bot_comment(t_asm *a, char *buf_comment, int *comment_exists)
{
	if (!buf_comment)
	{
		ft_putendl("Syntax error: incorrect comment");
		return (0);
	}
	if (*comment_exists > 0)
	{
		ft_strdel(&buf_comment);
		ft_putendl("Lexical error: incorrect number of comment statements");
		return (0);
	}
	if (!a->bot_comment)
		a->bot_comment = buf_comment;
	(*comment_exists)++;
	return (1);
}

int			errors(t_lst **list, int name_exists, int comment_exists)
{
	if (!*list)
	{
		ft_putendl("Syntax error: no commands");
		return (0);
	}
	if (!name_exists)
	{
		ft_putendl("Syntax error: no name ");
		return (0);
	}
	if (!comment_exists)
	{
		ft_putendl("Syntax error: no comment ");
		return (0);
	}
	return (1);
}

int			name_comment(t_lst **list, t_asm *a, int n_name, int n_comment)
{
	char	*tmp_buf_name;
	char	*tmp_buf_comment;
	int		arg;

	while (*list)
	{
		if ((*list)->str[0] != '#' && (*list)->str[0] != ';'
			&& (arg = str_name((*list)->str)))
		{
			tmp_buf_name = get_name(list, arg, NULL, 1);
			if (!set_bot_name(a, tmp_buf_name, &n_name))
				return (0);
		}
		else if ((*list)->str[0] != '#' && (*list)->str[0] != ';'
			&& (arg = str_comment((*list)->str)))
		{
			tmp_buf_comment = get_name(list, arg, NULL, 2);
			if (!set_bot_comment(a, tmp_buf_comment, &n_comment))
				return (0);
		}
		else if (is_command((*list)->str))
			break ;
		lst_next(list);
	}
	return (errors(list, n_name, n_comment));
}
