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

// write_name(t_lst *list)
// {

// }

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

int		validation_name(t_lst *list, t_asm *a)
{
	t_lst	*tmp;
	int		name_exists;
	int		comment_exists;

	tmp = list;
	name_exists = 0;
	comment_exists = 0;
	while (tmp)
	{
		if (tmp->str[0] != '#' && str_name(tmp->str) && (a->bot_name = get_name(&tmp, 5)))
			name_exists++;
		if (tmp->str[0] != '#' && str_comment(tmp->str) && (a->bot_comment = get_name(&tmp, 8)))
			comment_exists++;
		tmp = tmp->next;
	}
	if (!name_exists)
	{
		ft_putendl("Syntax error: no name "); 
		// at token[TOKEN][001:014]ENDLINE
		return (1);
	}
	if (name_exists > 1)
	{
		ft_putendl("Lexical error: incorrect number of name statements"); 
		// at [3:11]
		return (1);
	}
	if (!comment_exists)
	{
		ft_putendl("Syntax error: no comment "); 
		// at token[TOKEN][001:014]ENDLINE
		return (1);
	}
	if (comment_exists > 1)
	{
		ft_putendl("Lexical error: incorrect number of comment statements"); 
		// at [3:11]
		return (1);
	}
	printf("name: %s\n", a->bot_name);
	printf("comment: %s\n", a->bot_comment);
	return (0);
}
