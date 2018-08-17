#include "asm.h"

void		print_cmnds(t_cmnd	*new)
{
	printf("____________________________\n\n %s \n____________________________\n\n", "NEW COMMANDS LIST");
	while (new)
	{
		printf("label:%s command:%d \n args:%d %d %s \n\t%d %d %s \n\t%d %d %s \n", new->label, new->command_name, new->arg.arg_arr[0].type, new->arg.arg_arr[0].value, new->arg.arg_arr[0].text, 
		new->arg.arg_arr[1].type, new->arg.arg_arr[1].value, new->arg.arg_arr[1].text,
		new->arg.arg_arr[2].type, new->arg.arg_arr[2].value, new->arg.arg_arr[2].text);
		new = new->next;
	}
}

int				digits(int n)
{
	int			size;
	int			i;

	size = 1;
	i = 1;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n / i > 0)
	{
		size++;
		i *= 10;
	}
	size--;
	return (size);
}

int			ft_pow(int n, int pow)
{
	int			result;
	int				i;

	result = 1;
	i = 0;
	if (pow < 0)
		return (0);
	while (i++ < pow)
	{
		result *= n;
	}
	return (result);
}
