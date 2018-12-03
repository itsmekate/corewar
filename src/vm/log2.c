#include "vm.h"

// void		log_lives(t_corewar *corewar, t_player *player)
// {
// 	char	*buf;
// 	char	*buf1;
// 	char	*left_part;

// 	if (corewar->verbal & L_LIVE && corewar->cycle >= corewar->start)
// 	{
// 		buf = ft_itoa(player->number);
// 		buf1 = ft_strjoin("Player ", buf);
// 		free(buf);
// 		buf = ft_strjoin(buf1, " (");
// 		free(buf1);
// 		buf1 = ft_strdup(player->name);
// 		left_part = ft_strjoin(buf, buf1);
// 		free(buf);
// 		free(buf1);
// 		buf = ft_strjoin(left_part, ") is said to be alive");
// 		free(left_part);
// 		if (corewar->visual_mode)
// 			ft_lstadd(&corewar->log, ft_lstnew(buf, ft_strlen(buf) + 1));
// 		else
// 			ft_putendl_fd(buf, 1);
// 		free(buf);
// 	}
// }

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