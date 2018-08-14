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
	i = ft_strlen(label) + 1;
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

char		*get_arg_label(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] && str[i] != ',' && str[i] != ' ' && str[i] != '\t')
		i++;
	new = ft_strsub(str, 0, i);
	return (new);
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
		while ((*list)->str[i] && (*list)->str[i] != '%' && (*list)->str[i] != 'r' && (*list)->str[i] != '#' && !ft_isdigit((*list)->str[i]))
			i++;
		if ((*list)->str[i] == '%')
		{
			t.arg_arr[j].type = 2; //t_dir
			t.arg_arr[j].size = a->op_tab[n_command - 1].label_size;
			if ((*list)->str[i + 1] != ':')
			{
				t.arg_arr[j].text = NULL;
				t.arg_arr[j].value = ft_atoi((*list)->str + i + 1);
				i++;
			}
			else
			{
				i += 2;
				t.arg_arr[j].text = get_arg_label((*list)->str + i);
				t.arg_arr[j].value = 0;
			}
		}
		else if ((*list)->str[i] == 'r')
		{
			t.arg_arr[j].type = 1; //t_dir
			t.arg_arr[j].size = 1;
			if ((*list)->str[i + 1] != ':')
			{
				t.arg_arr[j].text = NULL;
				t.arg_arr[j].value = ft_atoi((*list)->str + i + 1);
				i++;
			}
			else
			{
				i += 2;
				t.arg_arr[j].text = get_arg_label((*list)->str + i);
				t.arg_arr[j].value = 0;
			}
		}
		else if (ft_isdigit((*list)->str[i]))
		{
			t.arg_arr[j].type = 3; //t_ind
			t.arg_arr[j].size = 2;
			t.arg_arr[j].value = ft_atoi((*list)->str + i);
			t.arg_arr[j].text = NULL;
		}
		else
			break;
		i += digits(t.arg_arr[j].value);
		j++;
	}
	while (j < 3)
	{
		t.arg_arr[j].size = 0;
		t.arg_arr[j].type = 0;
		t.arg_arr[j].value = 0;
		t.arg_arr[j].text = NULL;
		j++;
	}
	return (t);
}
