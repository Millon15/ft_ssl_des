
#include <stdio.h>

int		main()
{
	unsigned int	i = 1;
	unsigned int	j = 10;
	unsigned int	k = 100;
	unsigned int	l = 1000;

	printf("%i\n", j | i);
	j |= i;
	printf("%i\n", j);
	printf("%i\n", j | k);
	j |= k;
	printf("%i\n", j);
	return (0);
}