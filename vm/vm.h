#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include "op.h"
# include <stdio.h>

typedef struct		s_player
{
	char			*file;
	char			*start;
}					t_player;

typedef struct 		s_corewar
{
	int				visual_mode;
	int				dump;
	int				cycles_to_die;
	t_player		*players[MAX_PLAYERS + 1];
	int				players_num;
	char			map[MEM_SIZE];

}					t_corewar;

/*
** memory.c
*/

t_corewar			*new_corewar(void);
t_player			*new_player(char *file);
void				clear_player(t_player **player);
void				clear_corewar(t_corewar **corewar);
void				print_corewar(t_corewar *corewar);

/*
** init.c
*/

t_corewar			*create_corewar(char **agrv);

#endif