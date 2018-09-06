#include "vm.h"

void		set_point(t_point *point, char value, t_player *player)
{
	point->value = value;
	point->player = player;
	point->is_new = 1;
}