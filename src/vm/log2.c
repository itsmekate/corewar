#include "vm.h"

char		*log_func(int quantity, ...)
{
	va_list	args;
	char	*arg;
	char	*str;

	va_start(args, quantity);
	str = ft_strdup((char *)va_arg(args, char *));
	while (quantity != 1)
	{
		arg = (char *)va_arg(args, char *);
		ft_mleak(&str, ft_strjoin(str, arg));
		quantity--;
	}
	va_end(args);
	return (str);
}

void			print_contestants(t_corewar *corewar)
{
	int			i;
	t_player	*player;

	ft_putstr("Introducing contestants...\n");
	i = 0;
	while (i < corewar->players_num)
	{
		player = corewar->players[i];
		ft_putstr("* Player ");
		ft_putnbr(player->number);
		ft_putstr(", weighing ");
		ft_putnbr(player->size);
		ft_putstr(" bytes, \"");
		ft_putstr(player->name);
		ft_putstr("\" (\"");
		ft_putstr(player->comment);
		ft_putstr("\") !\n");
		i++;
	}
}
