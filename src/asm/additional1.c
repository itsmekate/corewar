/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 17:45:25 by etugoluk          #+#    #+#             */
/*   Updated: 2018/09/04 17:45:26 by etugoluk         ###   ########.fr       */
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

int			count_codage(t_args t)
{
	int		i;
	int		codage;

	i = 0;
	codage = 0;
	while (t.arg_arr[i].type && i < 3)
	{
		if (t.arg_arr[i].type == 1)
			codage += ft_pow(2, 6 - i * 2);
		else if (t.arg_arr[i].type == 2)
			codage += ft_pow(2, 7 - i * 2);
		else if (t.arg_arr[i].type == 3)
			codage += ft_pow(2, 7 - i * 2) + ft_pow(2, 6 - i * 2);
		i++;
	}
	return (codage);
}
