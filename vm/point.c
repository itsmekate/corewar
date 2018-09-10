#include "vm.h"

void		set_point(t_point *point, char value, t_player *player)
{
	point->value = value;
	point->player = player;
	point->is_new = 1;
}

int			get_color(int num)
{
	static int ctab[6] = {0xff0000, 0xff, 0xff00, 0xe6c800,
		0x00c8c8, 0xc800c8};

	while (num >= 6)
		num -= 6;
	return (ctab[num]);
}

int			get_color_new(int num)
{
	static int ctab[6] = {0xff6464, 0x6464ff, 0x64ff64, 0xFFE741,
		0x3CFFFF, 0xFF48FF};

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