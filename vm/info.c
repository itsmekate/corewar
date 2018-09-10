#include "vm.h"

static int	get_indexv(char value)
{
	static int	values[16] = {0x01, 0x02, 0x03, 0x04,
		0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
		0x0d, 0x0e, 0x0f, 0x10};
	int			i;

	i = 0;
	while (i < 16)
	{
		if (values[i] == (value & 0xff))
			return(i);
		i++;
	}
	return (-1);
}

int			get_cycles(char	value)
{
	static int	values[16] = {10, 5, 5, 10,
		10, 6, 6, 6, 20, 25, 25, 800,
		10, 50, 1000, 2};
	int	i;

	i = get_indexv(value);
	if (i == -1)
		return (-1);
	return (values[i]);
}