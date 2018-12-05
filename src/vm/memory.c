#include "vm.h"

t_corewar		*new_corewar(void)
{
	t_corewar	*res;
	int			i;

	if ((res = (t_corewar *)malloc(sizeof(t_corewar))))
	{
		res->visual_mode = 0;
		res->debug = 0;
		res->pause = 1;
		res->dump = -1;
		res->start = 0;
		res->verbal = 0;
		res->cycle_to_die = CYCLE_TO_DIE;
		i = -1;
		while (++i <= MAX_PLAYERS)
			res->players[i] = NULL;
		res->players_num = 0;
		ft_memset(res->map, '\0', ((MEM_SIZE) * sizeof(t_point)));
		res->cycle = 0;
		res->log = NULL;
		res->last_alive = 0;
		res->lives_all = 0;
	}
	return (res);
}

t_player		*new_player(char *file)
{
	t_player *res;

	if ((res = (t_player *)malloc(sizeof(t_player))))
	{
		res->number = 0;
		res->file = ft_strdup(file);
		res->start = 0;
		ft_memset(res->name, '\0', PROG_NAME_LENGTH + 1);
		res->size = 0;
		ft_memset(res->comment, '\0', COMMENT_LENGTH + 1);
		res->exec = NULL;
		res->process_num = 0;
	}
	return (res);
}

void			clear_player(t_player **player)
{
	free((*player)->file);
	if ((*player)->exec)
		free((*player)->exec);
	free(*player);
	*player = NULL;
}

void			clear_corewar(t_corewar **corewar)
{
	int		i;
	t_list	*lst;
	t_list	*next;

	i = 0;
	while (i < (*corewar)->players_num)
	{
		clear_player(&((*corewar)->players[i]));
		i++;
	}
	lst = (*corewar)->log;
	while (lst)
	{
		next = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = next;
	}
	free(*corewar);
	*corewar = NULL;
}

t_list			*obj_in_lst(void *obj)
{
	t_list	*lst;

	lst = ft_lstnew(NULL, 0);
	lst->content = obj;
	return (lst);
}
