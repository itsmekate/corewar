#include "vm.h"

void		set_point(t_point *point, char value, t_player *player)
{
	point->value = value;
	point->player = player;
	point->is_new = 1;
}

int			get_color(int num)
{
	static int ctab[6] = {COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW,
		COLOR_CYAN, COLOR_MAGENTA};

	while (num >= 6)
		num -= 6;
	return (ctab[num]);
}

int			get_index(int index)
{
	while (index >= MEM_SIZE)
		index -= MEM_SIZE;
	return (index);
}