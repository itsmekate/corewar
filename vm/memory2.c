#include "vm.h"

t_process	*new_procces(void)
{
	t_process *res;
	if ((res = (t_process *)malloc(sizeof(t_process))))
		ft_memset(res, '\0', sizeof(t_process));
	return (res);
}

t_process	*create_process(int position, t_player *player, t_corewar *corewar)
{
	t_process *res;

	if ((res = new_procces()))
	{
		res->position = get_index(position);
		res->player = player;
		res->command = corewar->map[get_index(position)].value;
		corewar->map[get_index(position)].process = res;
		res->cycle = get_cycles(res->command);
		res->reg[0] = 0xffffffff - player->number + 1;
	}
	return (res);
}

void		move_process(int index, t_process *process, t_corewar *corewar)
{
	corewar->map[process->position].process = NULL;
	process->position = get_index(process->position + index);
	corewar->map[process->position].process = process;
	process->command = corewar->map[process->position].value;
	process->cycle = get_cycles(process->command);
}

void		clear_process(t_process **process, size_t size)
{
	ft_memset(*process, '\0', size);
	free(*process);
	*process = NULL;
}

void		kill_process(t_corewar *corewar, t_process *process)
{
	t_list		*lst;
	t_list		*lst1;
	t_list		*lst0;
	t_process	*pr;

	//printf("kill_process\n");
	lst = corewar->processes;
	lst0 = NULL;
	while (lst)
	{
		//printf("lol\n");
		lst1 = lst->next;
		pr = lst->content;
		if (pr == process)
		{
			//printf("equal\n");
			if (!lst0)
				corewar->processes = lst1;
			else
				lst0->next = lst1;
			//printf("==\n");
			corewar->map[get_index(pr->position)].process = NULL;
			//printf("map\n");
			clear_process(&pr, sizeof(t_process));
			//printf("clear\n");
			free(lst);
			lst = NULL;
			//printf("process killed\n");
			return ;
		}
		lst0 = lst;
		lst = lst1;
	}
	//printf("no process_killed\n");
}
