#ifndef COREWAR_H
# define CPREWAR_H

# include "../libft/libft.h"

typedef struct		s_player
{
	char			*file;
}					t_player;

typedef struct 		s_corewar
{
	int				visual_mode;
	int				dump;
	int				cycles_to_die;
	t_player		*players[MAX_PLAYERS + 1];

}					t_corewar;

/*
** memory.c
*/

t_corewar			*create_corewar(char **agrv);
void				clear_corewar(t_corewar **corewar);

#endif