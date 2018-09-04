#include "vm.h"

t_corewar			*create_corewar(char **agrv)
{
	t_corewar *res;

	res = new_corewar();
	(void)agrv;
	return (res);
}