#include "asm.h"

char		*get_name(t_lst **list, int i)
{
	int		j;
	char	*new = NULL;
	int		tmp;

	j = 0;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t'))
		i++;
	if (!(*list)->str[i] || (*list)->str[i] != '"')
		return (NULL);
	i++;
	tmp = i;
	while ((*list)->str[i] != '"')
	{
		i++;
		j++;
		if (!(*list)->str[i])
		{
			if (!new)
			{
				if (i == 5)
					new = ft_memalloc(PROG_NAME_LENGTH);
				else
					new = ft_memalloc(COMMENT_LENGTH);
			}
			new = ft_strjoin(new, ft_strsub((*list)->str, tmp, i));
			new = ft_strjoin(new, "\n");
			tmp = 0;
			i = 0;
			(*list) = (*list)->next;
		}
	}
	if (!new)
	{
		if (i == 5)
			new = ft_memalloc(PROG_NAME_LENGTH);
		else
			new = ft_memalloc(COMMENT_LENGTH);
		new = ft_strncpy(new, (*list)->str + tmp, j);
	}
	else
		new = ft_strjoin(new, ft_strsub((*list)->str, tmp, i));
	i++;
	while ((*list)->str[i] && ((*list)->str[i] == ' ' || (*list)->str[i] == '\t'))
		i++;
	if ((*list)->str[i] && (*list)->str[i] != '#')
		return (NULL);
	(*list) = (*list)->next;
	return (new);
}

void		rotate(char *str, int size)
{
	int		i;
	char	tmp;
	int		s = size / 2;

	i = 0;
	if (size != 1)
		while (size != s)
		{
			tmp = str[i];
			str[i] = str[size - 1];
			str[size - 1] = tmp;
			i++;
			size--;
		}
}

int			sum_exec(t_cmnd *c)
{
	int		res;

	res = 0;
	while (c)
	{
		res += c->n_byte;
		c = c->next;
	}
	return (res);
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

int			count_codage(t_args t)
{
	int		i;
	int		codage;

	i = 0;
	codage = 0;
	while (t.arg_arr[i].type && i < 3)
	{
		if (t.arg_arr[i].type == 1)
			codage += ft_pow(2, 6 - i * 2);
		else if (t.arg_arr[i].type == 2)
			codage += ft_pow(2, 7 - i * 2);
		else if (t.arg_arr[i].type == 3)
			codage += ft_pow(2, 7 - i * 2) + ft_pow(2, 6 - i * 2);
		i++;
	}
	return (codage);
}

void		write_commands(int fd, t_cmnd *c, t_asm a)
{
	int		i;
	int		codage;

	i = 0;
	codage = 0;
	while (c)
	{
		write(fd, (void *)&c->command_name, 1);
		i = 0;
		if (a.op_tab[c->command_name - 1].acb)
		{
			codage = count_codage(c->arg);
			printf("CODAGE %d\n", codage);
			rotate((char *)&codage, 1);
			write(fd, &codage, 1);
		}
		while ((c->arg.arg_arr[i]).type && i < 3)
		{
			rotate((char *)&c->arg.arg_arr[i].value, c->arg.arg_arr[i].size);
			write(fd, (void *)&c->arg.arg_arr[i].value, c->arg.arg_arr[i].size);
			i++;
		}
		c = c->next;
	}
}

void		write_data(int fd, t_asm a)
{
	int		magic;
	char	*zeros;
	int		sum;

	magic = COREWAR_EXEC_MAGIC;
	zeros = ft_memalloc(4);
	sum = sum_exec(a.command);
	rotate((char *)&magic, 4);
	write(fd, &magic, 4);
	write(fd, a.bot_name, PROG_NAME_LENGTH);
	write(fd, zeros, 4);
	rotate((char *)&sum, 4);
	write(fd, &sum, 4);
	write(fd, a.bot_comment, COMMENT_LENGTH);
	write(fd, zeros, 4);
	write_commands(fd, a.command, a);
}

void		create_file(t_asm a)
{
	int		fd;
	char	*file_name;

	file_name = ft_strjoin(a.bot_name, ".cor");
	fd = open(file_name, O_WRONLY | O_CREAT, 0777);
	write_data(fd, a);
	close(fd);
}
