#include "asm.h"

char		*find_label(t_lst **list)
{
	char	*label;
	int		i;

	i = 0;
	label = NULL;
	if (!ft_strchr(LABEL_CHARS, (*list)->str[i]) || !ft_strchr((*list)->str, ':'))
		return (label);
	while ((*list)->str[i] && (*list)->str[i] != ':' && (*list)->str[i] != ' ' && (*list)->str[i] != '\t')
	{
		if (!ft_strchr(LABEL_CHARS, (*list)->str[i]))
			return (label);
		i++;
	}
	if (!(*list)->str[i] || (*list)->str[i] != ':')
		return (label);
	label = ft_strnew(i);
	label = strncpy(label, (*list)->str, i);
	return (label);
}

int			find_command_number(char *name, t_asm *a)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(name, a->op_tab[i].name))
			return (i + 1);
		i++;
	}
	return (0);
}

int			find_command_name(t_lst **list, char *label, t_asm *a)
{
	int		n;
	int		i;
	int		j;
	int		size;
	char	*name;

	n = 0;
	size = 0;
	i = ft_strlen(label);
	while (!ft_strchr(LABEL_CHARS, (*list)->str[i]))
	{
		if ((*list)->str[i] == ':')
			return (-1);
		if (!(*list)->str[i])
		{
			(*list) = (*list)->next;
			i = 0;
		}
		else
			i++;
	}
	j = i;
	while ((*list)->str[i] && ft_strchr(LABEL_CHARS, (*list)->str[i]))
	{
		size++;
		i++;
	}
	if ((*list)->str[i] == ':')
		return (-1);
	name = ft_strnew(size);
	name = strncpy(name, (*list)->str + j, size);
	n = find_command_number(name, a);
	return (n);
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

t_args		find_args(t_lst **list, char *label, int n_command, t_asm *a)
{
	t_args	t;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(label) + ft_strlen(a->op_tab[n_command - 1].name);
	t.n = a->op_tab[n_command - 1].nb_params;
	while (j < t.n)
	{
		while ((*list)->str[i] && (*list)->str[i] != '%' && (*list)->str[i] != 'r' && (*list)->str[i] != '#')
			i++;
		printf("%d smth %c\n", i, (*list)->str[i]);
		if ((*list)->str[i] == '%')
		{
			t.arg_arr[j].type = 2; //t_dir
			t.arg_arr[j].value = ft_atoi((*list)->str + i + 1);
			i++;
		}
		else if ((*list)->str[i] == 'r')
		{
			t.arg_arr[j].type = 1; //t_reg
			t.arg_arr[j].value = ft_atoi((*list)->str + i + 1);
			i++;
		}
		// else if (ft_isdigit((*list)->str[i]))
		// {
		// 	t.arg_arr[j].type = 3; //t_ind
		// 	t.arg_arr[j].value = ft_atoi((*list)->str + i);
		// 	continue ;
		// }
		else
			break;
		t.arg_arr[j].text = NULL;
		j++;
		// i += digits(t.arg_arr[j].value);
	}
	while (j < 3)
	{
		t.arg_arr[j].type = 0;
		t.arg_arr[j].value = 0;
		t.arg_arr[j].text = NULL;
		j++;
	}
	return (t);
}
