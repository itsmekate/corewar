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

void			set_unsigned_int(unsigned int value, int start_index, t_corewar *corewar, t_player *player)
{
	int i;

	i = 0;

	while (i < 4)
	{
		set_point(&corewar->map[get_index(start_index)], value >> 24, player);
		value = value << 8;
		start_index++;
		i++;
	}
}