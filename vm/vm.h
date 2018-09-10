#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>

# include <stdio.h>

typedef struct		s_player
{
	int				number;
	char			*file;
	int				start;
	int				color;
	char			name[PROG_NAME_LENGTH + 1];
	int				size;
	char			comment[COMMENT_LENGTH + 1];
	char			*exec;
	int				process_num;
}					t_player;

typedef struct 		s_process	
{
}					t_procces;

typedef struct 		s_point
{
	char			value;
	t_player		*player;
	int				is_new;
}					t_point;

<<<<<<< HEAD
typedef struct 		s_process
{
	int				position;
	int				carry;
	t_player		*player;
	int				alive;
	char			command;
	int				pause_cycle;
	int				reg[REG_NUMBER];
}					t_process;

=======
>>>>>>> 56a6343a91661fa169b299cf78fe127108b9cc4a
typedef struct 		s_corewar
{
	int				visual_mode;
	int				dump;
	int				cycle_to_die;
	t_player		*players[MAX_PLAYERS];
	int				players_num;
	t_point			map[MEM_SIZE];
	uintmax_t		cycle;
	t_list			*processes;
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

/*
** player.c
*/
int					parse_player(t_player *player);
int					get_color(int num);

/*
** point.c
*/
void				set_point(t_point *point, char value, t_player *player);

/*
** number.c
*/
int					is_number(t_corewar *corewar, char *s);
int					get_number(t_corewar *corewar, int num);

/*
**ncurses.c
*/
int					visualize(t_corewar *c);

#endif