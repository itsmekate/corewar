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

void		write_data(int fd)
{
	int		magic;

	magic = COREWAR_EXEC_MAGIC;
	write(fd, &magic, 4);
}

void		create_file(t_asm a)
{
	int		fd;
	char	*file_name;

	file_name = ft_strjoin(a.bot_name, ".cor");
	fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	write_data(fd);
	close(fd);
}
