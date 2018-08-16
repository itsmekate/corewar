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

void	add_to_list(char *str, t_lst *list)
{
	while (list->next)
		list = list->next;
	list->next = (t_lst*)malloc(sizeof(t_lst));
	list->next->str = ft_strdup(str);
	list->next->next = NULL;
}

t_lst	*ft_read(char *f, t_lst *list)
{
	t_lst	*head;
	int		fd;
	char	*tmp;

	fd = open(f, O_RDONLY);
	if (fd == 0 || fd == -1)
	{
		ft_putendl("ERROR");
		exit(0);
	}
	if (get_next_line(fd, &tmp) > 0)
	{
		list = (t_lst*)malloc(sizeof(t_lst));
		list->str = ft_strdup(tmp);
		list->next = NULL;
		free(tmp);
	}
	head = list;
	while (get_next_line(fd, &tmp) > 0)
	{
		add_to_list(tmp, list);
		free(tmp);
	}
	return (head);
}

int		validation(t_lst **list, t_asm *a)
{
	if (!validation_name(list, a))
		exit(0);
	get_t_op(a);
	validation_commands(list, a);
	return (0);
}

int	main(int argc, char **argv)
{
	t_lst	*list;
	t_asm	a;

	printf("counting %d\n", T_REG | T_IND | T_DIR);
	if (argc != 2)
		ft_putendl("ERROR");
	else
	{
		list = NULL;
		list = ft_read(argv[1], list);
		ft_putendl("READING DONE...");
		validation(&list, &a);
		create_file(a);
	}
	return (0);
}
