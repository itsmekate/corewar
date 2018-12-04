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
