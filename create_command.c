#include "asm.h"
#include "op.h"

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
	label = ft_strnew(i + 1);
	label = strncpy(label, str, i);
	return (label);
}
