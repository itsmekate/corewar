#include "vm.h"

t_corewar	*new_corewar(void)
{
	t_corewar	*res;
	int			i;

	if ((res = (t_corewar *)malloc(sizeof(t_corewar))))
	{
		res->visual_mode = 0;
		res->dump = 0;
		res->cycle_to_die = CYCLE_TO_DIE;
		i = -1;
		while (++i <= MAX_PLAYERS)
			res->players[i] = NULL;
		res->players_num = 0;
		ft_memset(res->map, '\0', MEM_SIZE * sizeof(t_point));
		res->cycle = 0;
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

void				clear_corewar(t_corewar **corewar)
{
	int		i;

	i = 0;
	while (i < (*corewar)->players_num)
	{
		clear_player(&((*corewar)->players[i]));
		i++;
	}
	free(*corewar);
	*corewar = NULL;
}

t_list		*obj_in_lst(void *obj)
{
	t_list	*lst;

	lst = ft_lstnew(NULL, 0);
	lst->content = obj;
	return (lst);
}

////
////
# define RED		"\x1B[31m"
# define RESET		"\x1B[0m"
# define GREEN		"\x1B[32m"

void 				print_map(t_corewar *corewar)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (i < MEM_SIZE)
	{
		if (n == 64)
		{
			printf("\n");
			n = 0;
		}
		n++;
		if (corewar->map[i].is_new)
			printf(GREEN);
		if (corewar->map[i].process)
			printf(RED);
		printf("%02x " RESET, corewar->map[i].value & 0xff);
		corewar->map[i].is_new = 0;
		i++;
	}
	printf("\n");
}

void				print_processes(t_corewar *corewar)
{
	t_list *lst;
	t_process *pr;

	lst = corewar->processes;
	while (lst)
	{
		pr = lst->content;
		printf("position %i, player %s, command %02x, cycle %i\n---\n", 
			pr->position, pr->player->name, pr->command & 0xff, pr->cycle);
		lst = lst->next;
	}
}

void				print_corewar(t_corewar *corewar)
{
	print_map(corewar);
	printf("visual %i, dump %i\ncycle to die %i\n", corewar->visual_mode,
		corewar->dump, corewar->cycle_to_die);
	int i = -1;
	printf("players num %i\n", corewar->players_num);
	while (++i < corewar->players_num)
	{
		printf("Player number %i\n", corewar->players[i]->number);
		printf("%s (%s), starts at %i;\nbot_size %i, comment: %s\n", corewar->players[i]->file,
		corewar->players[i]->name, corewar->players[i]->start, corewar->players[i]->size,
		corewar->players[i]->comment);
		int j = 0;
		while (j < corewar->players[i]->size)
		{
			printf("%02x ", corewar->players[i]->exec[j] & 0xff);
			j++;
		}
		printf("\n-----\n");
	}
	print_processes(corewar);
}
