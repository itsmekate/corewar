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

int		str_comment(char *str)
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

int		str_name(char *str)
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

int 	is_command(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			i++;
			continue;
		}
		if (str[i] == '#')
			return (0);
		else
			return (1);
	}
	return (0);
}

<<<<<<< HEAD
=======
char		*get_name(t_lst **list, int i)
{
	int		j;
	char	*new = NULL;
	int		tmp;

	j = 0;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t'))
		i++;
	if (!(*list)->str[i] || (*list)->str[i] != '"')
		return (NULL);
	i++;
	tmp = i;
	while ((*list)->str[i] != '"')
	{
		i++;
		j++;
		if (!(*list)->str[i])
		{
			if (!new)
			{
				if (i == 5)
					new = ft_memalloc(PROG_NAME_LENGTH);
				else
					new = ft_memalloc(COMMENT_LENGTH);
			}
			new = ft_strjoin(new, ft_strsub((*list)->str, tmp, i));
			new = ft_strjoin(new, "\n");
			tmp = 0;
			i = 0;
			(*list) = (*list)->next;
		}
	}
	if (!new)
	{
		if (i == 5)
			new = ft_memalloc(PROG_NAME_LENGTH);
		else
			new = ft_memalloc(COMMENT_LENGTH);
		new = ft_strncpy(new, (*list)->str + tmp, j);
	}
	else
		new = ft_strjoin(new, ft_strsub((*list)->str, tmp, i));
	i++;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t'))
		i++;
	if ((*list)->str[i] && (*list)->str[i] != '#')
		return (NULL);
	(*list) = (*list)->next;
	return (new);
}

>>>>>>> kprasol
int		validation_name(t_lst **list, t_asm *a)
{
	int		name_exists;
	int		comment_exists;

	name_exists = 0;
	comment_exists = 0;
	while (*list)
	{
		if ((*list)->str[0] != '#' && str_name((*list)->str) && (a->bot_name = get_name(list, 5)))
			name_exists++;
		if ((*list)->str[0] != '#' && str_comment((*list)->str) && (a->bot_comment = get_name(list, 8)))
			comment_exists++;
<<<<<<< HEAD
		if (is_command((*list)->str))
			break;
		(*list) = (*list)->next;
=======
		if (!*list)
		{
			ft_putendl("Syntax error: no commands");
			return (0);
		}
		if (is_command((*list)->str))
			break;
		(*list) = (*list)->next;
	}
	if (!*list)
	{
		ft_putendl("Syntax error: no commands");
		return (0);
>>>>>>> kprasol
	}
	if (!name_exists)
	{
		ft_putendl("Syntax error: no name "); 
		// at token[TOKEN][001:014]ENDLINE
		return (0);
	}
	if (name_exists > 1)
	{
		ft_putendl("Lexical error: incorrect number of name statements"); 
		// at [3:11]
		return (0);
	}
	if (!comment_exists)
	{
		ft_putendl("Syntax error: no comment "); 
		// at token[TOKEN][001:014]ENDLINE
		return (0);
	}
	if (comment_exists > 1)
	{
		ft_putendl("Lexical error: incorrect number of comment statements"); 
		// at [3:11]
		return (0);
	}
	printf("name: %s\n", a->bot_name);
	printf("comment: %s\n", a->bot_comment);
	return (1);
}
