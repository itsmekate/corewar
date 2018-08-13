#include "asm.h"

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
				new = ft_strnew(j);
			new = ft_strjoin(new, ft_strsub((*list)->str, tmp, i));
			new = ft_strjoin(new, "\n");
			tmp = 0;
			i = 0;
			(*list) = (*list)->next;
		}
	}
	if (!new)
	{
		new = ft_strnew(j);
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

// void		create_file(t_lst *list)
// {
// 	int		fd;
// 	char	*file_name;
// 	t_asm	a;

// 	if (!(a.bot_name = get_name(&list)))
// 	{
// 		ft_putendl("ERROR name");
// 		exit(0);
// 	}
// 	if (!(a.bot_comment = get_comment(&list)))
// 	{
// 		ft_putendl("ERROR comment");
// 		exit(0);
// 	}
// 	file_name = ft_strjoin(a.bot_name, ".cor");
// 	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
// 	close(fd);
// 	printf("bot name: %s\n", a.bot_name);
// 	printf("bot comment: %s\n", a.bot_comment);

// 	get_t_op(&a);
// 	get_lst_commands(&a, &list);
// }
