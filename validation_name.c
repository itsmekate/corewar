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

int		validation_name(t_lst *list)
{
	t_lst	*tmp;
	int		name_exists;
	char	*name;

	tmp = list;
	name_exists = 0;
	while (tmp)
	{
		if (ft_strstr(tmp->str, ".name") && tmp->str[0] != '#')
		{
			name = tmp->str;
			name_exists++;
		}
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
	if (name)
	{
		if (!ft_strchr(name, '\"'))
		{
			ft_putendl("Syntax error: no parantheses "); 
			// at token[TOKEN][001:007] INSTRUCTION \"zork\"
			return (1);
		}
		// when name exists and there is at least one \"
		// else
		// {

		// }
	}
	system("leaks asm");
	return (0);
}
