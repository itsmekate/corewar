#include "asm.h"

char		*get_name(t_lst **list)
{
	int		i;
	char	*new;

	while (!ft_strlen((*list)->str) || (*list)->str[0] == '#')
		(*list) = (*list)->next;
	if (ft_strlen((*list)->str) <= 8 || ft_strncmp(NAME_CMD_STRING, (*list)->str, 5))
		return (NULL);
	i = 5;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t' || (*list)->str[i] == '"'))
		i++;
	new = ft_strnew(ft_strlen((*list)->str) - i - 1);
	new = ft_strncpy(new, (*list)->str + i, ft_strlen((*list)->str) - i - 1);
	(*list) = (*list)->next;
	return (new);
}

char		*get_comment(t_lst **list)
{
	int		i;
	char	*new;

	while (!ft_strlen((*list)->str) || (*list)->str[0] == COMMENT_CHAR)
		(*list) = (*list)->next;
	if (ft_strlen((*list)->str) <= 11 || ft_strncmp(COMMENT_CMD_STRING, (*list)->str, 8))
		return (NULL);
	i = 9;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t' || (*list)->str[i] == '"'))
		i++;
	new = ft_strnew(ft_strlen((*list)->str) - i - 1);
	new = ft_strncpy(new, (*list)->str + i, ft_strlen((*list)->str) - i - 1);
	(*list) = (*list)->next;
	return (new);	
}

t_cmnd		*new_command(char *str, t_asm *a)
{
	t_cmnd	*new;

	printf("%s\n", str);
	new = (t_cmnd *)malloc(sizeof(t_cmnd));
	new->label = find_label(str);
	new->command_name = find_command_name(str, new->label, a);
	new->arg = find_args(str, new->label, new->command_name, a);
	// printf("%d %d %d %d %d %d\n", new->arg.arg_arr[0].type, new->arg.arg_arr[0].value, new->arg.arg_arr[1].type, new->arg.arg_arr[1].value, new->arg.arg_arr[2].type, new->arg.arg_arr[2].value);
	new->n_byte = 0;
	new->next = NULL;
	return (new);
}

void		get_lst_commands(t_asm *a, t_lst **list)
{
	t_cmnd	*head;

	while (!ft_strlen((*list)->str) || (*list)->str[0] == COMMENT_CHAR)
		(*list) = (*list)->next;
	a->command = new_command((*list)->str, a);
	head = a->command;
	(*list) = (*list)->next;
	while ((*list))
	{
		if (!ft_strlen((*list)->str) || (*list)->str[0] == COMMENT_CHAR)
		{
			(*list) = (*list)->next;
			continue;
		}
		head->next = new_command((*list)->str, a);
		head = head->next;
		(*list) = (*list)->next;
	}
}

void		create_file(t_lst *list)
{
	int		fd;
	char	*file_name;
	t_asm	a;

	if (!(a.bot_name = get_name(&list)))
	{
		ft_putendl("ERROR name");
		exit(0);
	}
	if (!(a.bot_comment = get_comment(&list)))
	{
		ft_putendl("ERROR comment");
		exit(0);
	}
	file_name = ft_strjoin(a.bot_name, ".cor");
	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	close(fd);
	printf("bot name: %s\n", a.bot_name);
	printf("bot comment: %s\n", a.bot_comment);

	get_t_op(&a);
	get_lst_commands(&a, &list);
}
