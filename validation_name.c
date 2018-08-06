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

int		str_name(char *str)
{
	char	*tmp;

	tmp = ft_strsub(str, 0, 5);
	if (!ft_strcmp(tmp, ".name"))
		return (1);
	return (0);
}

int		validation_name(t_lst *list)
{
	t_lst	*tmp;
	int		name_exists;
	int		comment_exists;
	// char	*name;

	tmp = list;
	name_exists = 0;
	comment_exists = 0;
	while (tmp)
	{
		if (ft_strstr(tmp->str, ".name") && tmp->str[0] != '#'
			&& str_name(tmp->str) && get_name(tmp))
			name_exists++;
		// if (ft_strstr(tmp->str, ".comment") && tmp->str[0] != '#')
		// {
		// 	write_comment(tmp);
		// 	comment_exists++;
		// }
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
	return (0);
}
