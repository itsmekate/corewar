#include "asm.h"

char		*find_label(char *str)
{
	char	*label;
	int		i;

	i = 0;
	label = NULL;
	if (!ft_strchr(LABEL_CHARS, str[i]) || !ft_strchr(str, ':'))
		return (label);
	while (str[i] && str[i] != ':' && str[i] != ' ' && str[i] != '\t')
		i++;
	if (!str[i] || str[i] != ':')
		return (label);
	label = ft_strnew(i);
	label = strncpy(label, str, i);
	return (label);
}

int			find_command_number(char *name, t_asm *a)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (i < 17)
	{
		if (!ft_strcmp(name, a->op_tab[i].name))
			return (i + 1);
		i++;
	}
	return (0);
}

int			find_command_name(char *str, char *label, t_asm *a)
{
	int		n;
	int		i;
	int		j;
	int		size;
	char	*name;

	n = 0;
	size = 0;
	i = ft_strlen(label);
	while (str[i] && !ft_strchr(LABEL_CHARS, str[i]))
		i++;
	j = i;
	while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
	{
		size++;
		i++;
	}
	name = ft_strnew(size);
	name = strncpy(name, str + j, size);
	n = find_command_number(name, a);
	return (n);
}
