#ifndef COREWAR_H
# define COREWAR_H

# include "../libft/libft.h"
# include "op.h"
# include <fcntl.h>
# include <ncurses.h>

# include <stdio.h>

# define L_LIVE			1
# define L_CYCLE		2
# define L_FUNC			4
# define L_DEATH		8
# define L_MOVE			16

typedef struct		s_player
{
	int				number;
	char			*file;
	int				start;
	char			name[PROG_NAME_LENGTH + 1];
	int				size;
	char			comment[COMMENT_LENGTH + 1];
	char			*exec;
	int				process_num;
}					t_player;

typedef struct 		s_process
{
	int				position;
	int				carry;
	t_player		*player;
	int				alive;
	char			command;
	int				cycle;
	int				reg[REG_NUMBER];
}					t_process;

typedef struct 		s_point
{
	char			value;
	t_player		*player;
	int				is_new;
	t_process		*process;
}					t_point;

typedef struct 		s_corewar
{
	int				visual_mode;
	int				verbal;
	int				start;
	int				dump;
	int				cycle_to_die;
	t_player		*players[MAX_PLAYERS];
	int				players_num;
	t_point			map[MEM_SIZE];
	int				cycle;
	t_list			*processes;
	int				pause;
	void			(*f[16]) (struct s_corewar *, t_process *);
	t_list			*log;
}					t_corewar;

/*
** ncurses
*/
typedef struct		s_window
{
	WINDOW			*field;
	WINDOW			*score;
	int				h;
	int				score_row;
}					t_window;

typedef struct		s_field
{
	int				row;
	int				col;
}					t_field;

/*
** memory.c
*/
t_corewar			*new_corewar(void);
t_player			*new_player(char *file);
void				clear_player(t_player **player);
void				clear_corewar(t_corewar **corewar);
t_list				*obj_in_lst(void *obj);
//
void				print_corewar(t_corewar *corewar);


/*
** memory2.c
*/
void				kill_process(t_corewar *corewar, t_process *process);
t_process			*new_procces(void);
void				clear_process(t_process **process, size_t size);
void				move_process(int index, t_process *process, t_corewar *corewar);
t_process			*create_process(int position, t_player *player, t_corewar *corewar);


/*
** init.c
*/
t_corewar			*create_corewar(char **agrv);

/*
** player.c
*/
int					parse_player(t_player *player);
int					get_color(int num);
int					get_color_new(int num);

/*
** point.c
*/
void				set_point(t_point *point, char value, t_player *player);
int					get_color(int num);
int					get_color_new(int num);
unsigned int					get_index(unsigned int index);

/*
** number.c
*/
int					get_number(t_corewar *corewar, int num);
int					is_number(char *s);

/*
**ncurses.c
*/
int					visualize(t_corewar *c);

/*
**ncurses2.c
*/
void				print_field(t_corewar *c, t_window win);
int					print_players(t_corewar *c, t_window win);

/*
**info.c
*/
int					get_cycles(char	value);
void				init_commands(t_corewar *corewar);
int					get_label(char	value);

/*
**cycle.c
*/
void				grand_cycle(t_corewar *corewar);

/*
**log.c
*/
void				print_log(t_list *log);
void				log_cycle(t_corewar *corewar);
void				log_move(t_corewar *corewar, t_process *process, int move);
void				print_contestants(t_corewar *corewar);
void				log_cycle_to_die(t_corewar *corewar);


/*
**functions
*/
void				live(t_corewar *corewar, t_process *process);
void				load(t_corewar *corewar, t_process *process);
void				store(t_corewar *corewar, t_process *process);
void				addition(t_corewar *corewar, t_process *process);
void				substraction(t_corewar *corewar, t_process *process);
void				ft_and(t_corewar *corewar, t_process *process);
void				ft_or(t_corewar *corewar, t_process *process);
void				ft_xor(t_corewar *corewar, t_process *process);
void				zjump(t_corewar *corewar, t_process *process);
void				load_index(t_corewar *corewar, t_process *process);
void				store_index(t_corewar *corewar, t_process *process);
void				ft_fork(t_corewar *corewar, t_process *process);
void				long_load(t_corewar *corewar, t_process *process);
void				long_load_index(t_corewar *corewar, t_process *process);
void				long_fork(t_corewar *corewar, t_process *process);
void				aff(t_corewar *corewar, t_process *process);
unsigned int		get_arg(int size, int start_index, t_corewar *corewar);
void				set_unsigned_int(unsigned int value, int start_index, t_corewar *corewar, t_player *player);
unsigned int		get_value(unsigned int arg, t_process *process, t_corewar *corewar, int *move);
void				get_types(unsigned int *arg, t_process *process, t_corewar *corewar);
void				error_codage(unsigned int *arg, t_process *process, t_corewar *corewar);
t_process			*copy_process(t_process *process);


void 				print_map(t_corewar *corewar);
void 				dump_map(t_corewar *corewar);

#endif