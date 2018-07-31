#include "asm.h"

char		*get_name(char *str)
{
	int		i;
	char	*new;

	i = 5;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '"'))
		i++;
	new = ft_strnew(ft_strlen(str) - i - 1);
	new = ft_strncpy(new, str + i, ft_strlen(str) - i - 1);
	return (new);
}

void		create_file(t_lst *list)
{
	int		fd;
	char	*name;

	if (ft_strlen(list->str) <= 8 && ft_strncmp(".name", list->str, 5))
	{
		ft_putendl("ERROR");
		exit(0);
	}
	name = ft_strjoin(get_name(list->str), ".cor");
	fd = open(name, O_WRONLY | O_APPEND | O_CREAT);
	close(fd);
	free(name);
}
