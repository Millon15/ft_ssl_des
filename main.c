
#include <unistd.h>
#include <stdio.h>

int		main()
{
	char	*a = getpass();
	printf("%s\n", a);
}
