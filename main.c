
#include "ft_printf/libft/libft.h"
#include "fcntl.h"

int		main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);

	ft_putnbr(fd);
	write(fd, "sfas\n", 5);
	close(fd);
	return (0);
}
