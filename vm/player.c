#include "vm.h"

int			get_color(int num)
{
	static int ctab[6] = {0xff0000, 0xff, 0xff00, 0xe6c800, 0x00c8c8, 0xc800c8};

	while (num >= 6)
		num -= 6;
	return (ctab[num]);
}

static int	check_header(int fd)
{
	int		i;
	char	s;

	i = 0;
	while (i < 4)
	{
		read (fd, &s, 1);
		if ((COREWAR_EXEC_MAGIC << (8 * i) >> 24) != s)
			return (0);
		i++;
	}
	return (1);
}

static int	add_info(int fd, char *dest, int size, int mode)
{
	int		i;
	char	c;

	i = 0;
	while (i < size)
	{
		read(fd, &(dest[i]), 1);
		if (mode && dest[i] && !ft_isprint(dest[i]))
			return (0);
		i++;
	}
	dest[i] = '\0';
	i = 0;
	while (mode && i < 4)
	{
		read(fd, &c, 1);
		if (c)
			return (0);
		i++;
	}
	return (1);
}

static int	add_size(int fd, t_player *player)
{
	int i;
	char c;
	int res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		read(fd, &c, 1);
		res += c << (24 - (8 * i));
		i++;
	}
	if (res > CHAMP_MAX_SIZE || res < 1)
		return (0);
	player->size = res;
	return (1);
}

int			parse_player(t_player *player)
{
	int				fd;
	int				status;
	char			n;

	status = 0;
	if ((fd = open(player->file, O_RDONLY)) > 0)
	{
		status = check_header(fd);
		if (status)
			status = add_info(fd, player->name, PROG_NAME_LENGTH, 1);
		if (status)
			status = add_size(fd, player);
		if (status)
			status = add_info(fd, player->comment, COMMENT_LENGTH, 1);
		player->exec = (char *)malloc(sizeof(char) * (player->size + 1));
		if (status)
			status = add_info(fd, player->exec, player->size, 0);
		if (read(fd, &n, 1) == 1)
			status = 0;
		close(fd);
	}
	return (status);
}
