
#include <stdio.h>
#include <stdlib.h>

void	bad_malloc(void)
{
	printf("[FATAL ERROR]: Malloc error\n");
	exit (1);
}

void	bad_file(void)
{
	printf("[FATAL ERROR]: Wrong test file\n");
	exit (1);
}

void	bad_input(void)
{
	printf("[FATAL ERROR]: Wrong function input\n");
	exit (1);
}
