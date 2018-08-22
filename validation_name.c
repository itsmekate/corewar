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

int 		is_command(char *str)
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

char	*copy_n(char *dst, const char *src, int i, int len, int arg)
{
	int j;

	j = 0;
	if (!dst)
	{
		dst = (arg == 5) ? ft_memalloc(PROG_NAME_LENGTH) : ft_memalloc(COMMENT_LENGTH);
		dst = copy_n(dst, src, i, len, arg);
		return (dst);
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


char		*get_name(t_lst **list, int arg)
{
	char	*new;
	int		tmp;
	int		i;

	new = NULL;
	i = arg;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t'))
		i++;
	if (!(*list)->str[i] || (*list)->str[i] != '"')
		return (NULL);
	tmp = ++i;
	while ((*list)->str[i] != '"')
	{
		i++;
		if (!(*list)->str[i])
		{
			new = copy_n(new, (*list)->str + tmp, ft_strlen(new), i - tmp, arg);
			tmp = 0;
			i = 0;
			lst_next(list);
		}
	}
	new = copy_n(new, (*list)->str + tmp, ft_strlen(new), i - tmp, arg);
	i++;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t'))
		i++;
	if ((*list)->str[i] && (*list)->str[i] != '#' && (*list)->str[i] != ';')
		return (NULL);
	return (new);
}

int		set_bot_name(t_asm *a, char *tmp_buf_name, int *name_exists)
{
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

int		set_bot_comment(t_asm *a, char *tmp_buf_comment, int *comment_exists)
{
	if (*comment_exists > 0)
	{
		ft_strdel(&tmp_buf_comment);
		ft_putendl("Lexical error: incorrect number of comment statements");
		return (0);
	}
	if (!a->bot_comment)
		a->bot_comment = tmp_buf_comment;
	(*comment_exists)++;
	return (1);
}

int 	errors(t_lst **list, int name_exists, int comment_exists)
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

int		validation_name(t_lst **list, t_asm *a)
{
	int		name_exists;
	int		comment_exists;
	char	*tmp_buf_name;
	char	*tmp_buf_comment;

	name_exists = 0;
	comment_exists = 0;
	while (*list)
	{
		if ((*list)->str[0] != '#' && (*list)->str[0] != ';' && str_name((*list)->str) && (tmp_buf_name = get_name(list, 5)))
		{
			if (!set_bot_name(a, tmp_buf_name, &name_exists))
				return (0);
		}
		else if ((*list)->str[0] != '#' && (*list)->str[0] != ';' && str_comment((*list)->str) && (tmp_buf_comment = get_name(list, 8)))
		{
			if (!set_bot_comment(a, tmp_buf_comment, &comment_exists))
				return (0);
		}
		else if (is_command((*list)->str))
		{
			break;
		}
		lst_next(list);
	}
	printf("name %s\n", a->bot_name);
	printf("comment %s\n", a->bot_comment);
	if (!errors(list, name_exists, comment_exists))
		return (0);
	return (1);
}
