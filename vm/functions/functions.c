#include "../vm.h"

unsigned int	get_arg(int size, int start_index, t_corewar *corewar)
{
	char			res[4];
	unsigned int	arg;
	int				i;

	ft_memset(res, '\0', 4);
	i = -1;
	while (++i < size)
		res[size - 1 - i] = corewar->map[get_index(start_index + i)].value & 0xff;
	arg = *(unsigned int *)res;
	return (arg);
}