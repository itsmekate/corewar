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

// char		*get_comment(t_lst **list)
// {
// 	int		i;
// 	char	*new;

// 	while (!ft_strlen((*list)->str) || (*list)->str[0] == COMMENT_CHAR)
// 		(*list) = (*list)->next;
// 	if (ft_strlen((*list)->str) <= 11 || ft_strncmp(COMMENT_CMD_STRING, (*list)->str, 8))
// 		return (NULL);
// 	i = 9;
// 	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t' || (*list)->str[i] == '"'))
// 		i++;
// 	new = ft_strnew(ft_strlen((*list)->str) - i - 1);
// 	new = ft_strncpy(new, (*list)->str + i, ft_strlen((*list)->str) - i - 1);
// 	(*list) = (*list)->next;
// 	return (new);	
// }

// t_cmnd		*new_command(char *str, t_asm *a)
// {
// 	t_cmnd	*new;

// 	printf("%s\n", str);
// 	new = (t_cmnd *)malloc(sizeof(t_cmnd));
// 	new->label = find_label(str);
// 	new->command_name = find_command_name(str, new->label, a);
// 	new->t_dir = 0;
// 	new->t_reg = 0;
// 	new->t_ind = 0;
// 	new->n_byte = 0;
// 	new->next = NULL;
// 	return (new);
// }

// void		get_lst_commands(t_asm *a, t_lst **list)
// {
// 	t_cmnd	*head;

// 	while (!ft_strlen((*list)->str) || (*list)->str[0] == COMMENT_CHAR)
// 		(*list) = (*list)->next;
// 	a->command = new_command((*list)->str, a);
// 	head = a->command;
// 	(*list) = (*list)->next;
// 	while ((*list))
// 	{
// 		if (!ft_strlen((*list)->str) || (*list)->str[0] == COMMENT_CHAR)
// 		{
// 			(*list) = (*list)->next;
// 			continue;
// 		}
// 		head->next = new_command((*list)->str, a);
// 		head = head->next;
// 		(*list) = (*list)->next;
// 	}
// }

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
