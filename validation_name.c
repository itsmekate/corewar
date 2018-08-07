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

int		str_name(char *str)
{
	char	*tmp;

	tmp = ft_strsub(str, 0, 5);
	if (!ft_strcmp(tmp, ".name"))
		return (1);
	return (0);
}

int		str_comment(char *str)
{
	char	*tmp;

	tmp = ft_strsub(str, 0, 8);
	if (!ft_strcmp(tmp, ".comment"))
		return (1);
	return (0);
}


int		validation_name(t_lst *list)
{
	t_lst	*tmp;
	int		name_exists;
	int		comment_exists;
	int		not_exists;

	tmp = list;
	name_exists = 0;
	comment_exists = 0;
	while (tmp)
	{
		if (ft_strstr(tmp->str, ".name") && tmp->str[0] != '#'
			&& str_name(tmp->str) && get_name(tmp, 5))
			name_exists++;
		if (ft_strstr(tmp->str, ".comment") && tmp->str[0] != '#'
			&& str_comment(tmp->str) && get_name(tmp, 8))
				comment_exists++;
		tmp = tmp->next;
	}

	(!comment_exists) ? (not_exists = ft_printf("Syntax error: no comment\n")) : 0; 
	(comment_exists > 1) ? (not_exists = ft_printf("Lexical error: incorrect number of comment statements\n")) : 0;
	(!name_exists) ? (not_exists = ft_printf("Syntax error: no name\n")) : 0; 
	(!name_exists) ? (not_exists = ft_printf("Lexical error: incorrect number of name statements\n")) : 0; 
	if (not_exists)
		return (1);
	return (0);
}
