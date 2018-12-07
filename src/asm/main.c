/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 16:25:52 by etugoluk          #+#    #+#             */
/*   Updated: 2018/08/14 16:25:53 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		add_to_list(char *str, t_lst *list, int i)
{
	while (list->next)
		list = list->next;
	list->next = (t_lst*)malloc(sizeof(t_lst));
	list->next->str = ft_strdup(str);
	list->next->n_str = i;
	list->next->next = NULL;
}

t_lst		*ft_read(char *f, t_lst *list, int i)
{
	int		fd;
	char	*tmp;

	fd = open(f, O_RDONLY);
	if (fd == 0 || fd == -1)
	{
		ft_printf("Can't read source file %s\n", f);
		exit(0);
	}
	if (get_next_line(fd, &tmp) > 0)
	{
		list = (t_lst*)malloc(sizeof(t_lst));
		list->str = ft_strdup(tmp);
		list->n_str = i;
		list->next = NULL;
		free(tmp);
	}
	while (get_next_line(fd, &tmp) > 0)
	{
		add_to_list(tmp, list, ++i);
		free(tmp);
	}
	return (list);
}

void		get_asm(t_lst **list, t_asm *a)
{
	if (!name_comment(list, a, 0, 0))
	{
		exit(0);
	}
	get_t_op(a);
	if (!validation_commands(list, a))
	{
		exit(0);
	}
}

int			main(int argc, char **argv)
{
	t_lst	*list;
	t_asm	a;
	int		arg;
	int		k;

	if (argc < 2)
	{
		ft_putendl("Usage: ./asm [-a] <sourcefile.s>");
		return (0);
	}
	list = NULL;
	if ((arg = a_flag(argc, argv)))
		k = 1;
	else
	{
		k = 0;
		arg = argc - 1;
	}
	list = ft_read(argv[arg], list, 1);
	get_asm(&list, &a);
	(k == 1) ? a_bonus(a) : create_file(a, argv[arg]);
	return (0);
}
