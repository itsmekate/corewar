#include "get_next_line.h"

int		check_line(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] && str[i] != ';' && str[i] != '#')
		return (0);
	return (1);
}
