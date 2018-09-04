#include "vm.h"

int		parse_player(t_player *player)
{
	int		fd;
	char	n[2];

	if ((fd = open(player->file, O_RDONLY)) > 0)
	{
		int i = 0;
		while (read(fd, &n, 2) > 0)// && i++ < 50)
		{
			if (i++ % 16 == 0)
				printf("\n");
			printf("%04hx ", *(short int *)n);
		}
		printf("\n-------------\n");
		return (1);
	}
	return (0);
}