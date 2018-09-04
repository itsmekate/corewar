#include "vm.h"

static int	check_header(int fd)
{
	int		i;
	char s;

	i = 0;
	while (i < 4)
	{
		read (fd, &s, 1);
		if ((COREWAR_EXEC_MAGIC << (8 * i) >> 24) != s)
			return (0);
		i++;
	}
	return(1);
}

int			parse_player(t_player *player)
{
	int		fd;

	if ((fd = open(player->file, O_RDONLY)) > 0)
	{
		if (check_header(fd))
			return (1);
		close(fd);
	}
	return (0);
}