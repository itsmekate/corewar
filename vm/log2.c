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

void		log_func(t_corewar *corewar, ...)
{
	va_list	args;
	char	*buf;
	char	*res;
	int		quantity;

	if (corewar->verbal & L_FUNC && corewar->cycle >= corewar->start)
	{
		va_start(args, corewar);
		printf("after va_start\n");

		quantity = va_arg(args, int);
		printf("quantity %i\n", quantity);
		
		char *str = (char *)va_arg(args, char *);
		printf("str: %s\n", str);

		res = strdup(str);
		printf("res (ft_strdup elem via va_arg)%s\n", res);
		
		while (quantity != 1)
		{
			buf = ft_strdup((char *)va_arg(args, char *));
			printf("buf in cycle: %s\n", buf);
			
			ft_mleak(&res, ft_strjoin(res, buf));
			printf("res in cycle after ft_mleak: %s\n", res);

			// free(buf);
			quantity--;
			printf("quantity-- in cycle %i\n", quantity);

		}
		va_end(args);
		printf("after va_end %i\n", quantity);

		if (corewar->visual_mode)
			ft_lstadd(&corewar->log, ft_lstnew(res, ft_strlen(res) + 1));
		else
			ft_putendl_fd(res, 1);
		// free(res);
		printf("end of log_func\n");
	}
}