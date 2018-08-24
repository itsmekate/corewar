#include "asm.h"

void		arg_reg(t_args	*t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 1; //t_reg
	t->arg_arr[j].size = 1;
	if (str[*i + 1] != ':')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(str + *i + 1);
		(*i)++;
	}
	else
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
}

void		arg_dir(t_args	*t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 2; //t_dir
	if (str[*i + 1] != ':')
	{
		t->arg_arr[j].text = NULL;
		t->arg_arr[j].value = ft_atoi(str + *i + 1);
		(*i)++;
	}
	else
	{
		*i += 2;
		t->arg_arr[j].text = get_arg_label(str + *i);
		t->arg_arr[j].value = 0;
	}
}

void		arg_ind(t_args	*t, int j, int *i, char *str)
{
	t->arg_arr[j].type = 3; //t_ind
	t->arg_arr[j].size = 2;
	if (*str == ':')
	{
		(*i)++;
		t->arg_arr[j].text = get_arg_label(str + 1);
		t->arg_arr[j].value = 0;
	}
	else
	{
		t->arg_arr[j].value = ft_atoi(str);
		t->arg_arr[j].text = NULL;
	}
}

void		arg_zero(t_args	*t, int j)
{
	t->arg_arr[j].size = 0;
	t->arg_arr[j].type = 0;
	t->arg_arr[j].value = 0;
	t->arg_arr[j].text = NULL;
}

t_args		find_args(t_lst **list, int n_command, t_asm *a)
{
	t_args	t;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while ((*list)->str[i])
	{
		while ((*list)->str[i] && (*list)->str[i] != '%' && (*list)->str[i] != 'r' &&
			(*list)->str[i] != '#' && (*list)->str[i] != ';' && !ft_isdigit((*list)->str[i]) &&
			(*list)->str[i] != '-' && (*list)->str[i] != ':')
		{
			if ((*list)->str[i] == ' ' || (*list)->str[i] == '\t')
				i++;
			else
			{
				t.arg_arr[0].type = 0;
				return t;
			}
		}
		if ((*list)->str[i] == '%')
		{
			t.arg_arr[j].size = a->op_tab[n_command - 1].label_size;
			arg_dir(&t, j, &i, (*list)->str);
		}
		else if ((*list)->str[i] == 'r')
			arg_reg(&t, j, &i, (*list)->str);
		else if (ft_isdigit((*list)->str[i]) || (*list)->str[i] == '-' || (*list)->str[i] == ':')
			arg_ind(&t, j, &i, (*list)->str + i);
		else
			break;
		i += digits_char((*list)->str + i);
		if (find_comma((*list)->str + i) == -1)
		{
			t.arg_arr[0].type = 0;
			return t;
		}
		else
			i += find_comma((*list)->str + i);
		j++;
	}
	if (j > 3)
	{
		t.arg_arr[0].type = 0;
		return t;
	}
	while (j < 3)
		arg_zero(&t, j++);
	return (t);
}
