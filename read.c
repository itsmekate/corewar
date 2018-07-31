/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 15:15:31 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/31 15:15:35 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int argc, char **argv)
{
	t_lst	*list;

	if (argc != 2)
		ft_putendl("ERROR");
	else
	{
		ft_putendl(argv[1]);
		list = (t_lst*)malloc(sizeof(t_lst));
	}
	return (0);
}
