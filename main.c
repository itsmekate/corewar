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

t_lst		*ft_read(char *f, t_lst *list)
{
	t_lst	*head;
	int		fd;
	int		i;
	char	*tmp;

	i = 1;
	fd = open(f, O_RDONLY);
	if (fd == 0 || fd == -1)
	{
		ft_putendl("Wrong file");
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
	head = list;
	while (get_next_line(fd, &tmp) > 0)
	{
		add_to_list(tmp, list, ++i);
		free(tmp);
	}
	return (head);
}

void		validation(t_lst **list, t_asm *a)
{
	if (!validation_name(list, a))
		exit(0);
	get_t_op(a);
	if (!validation_commands(list, a))
	{
		system("leaks asm");
		exit(0);
	}
}

int			main(int argc, char **argv)
{
	t_lst	*list;
	t_asm	a;

	if (argc < 2)
	{
		ft_putendl("Usage:./asm [file_name.s]");
		return (0);
	}
	list = NULL;
	list = ft_read(argv[argc - 1], list);
	// ft_putendl("READING DONE...");
	validation(&list, &a);
	create_file(a, argv[argc - 1]);
	system("leaks asm");
	return (0);
}
