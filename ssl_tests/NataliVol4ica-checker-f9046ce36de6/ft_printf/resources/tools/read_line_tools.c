
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

size_t	as_you_wish = 0;

t_line	*new_readline(char *file, char *flags)
{
	t_line	*l;

	if (!(l = (t_line*)malloc(sizeof(t_line))))
		bad_malloc();
	if (!(l->str = (char*)malloc(sizeof(char) * 100000)))
		bad_malloc();
	l->len = 0;
	l->filename = ft_strdup(file);
	l->fd = fopen(file, flags);
	return (l);
}

void	close_readline(t_line *l)
{
	fclose(l->fd);
	free(l->filename);
	free(l->str);
	free(l);
}

int		read_line(t_line *line)
{
	line->len = getline(&line->str, &as_you_wish, line->fd);
	if (line->len > 0 && line->str[line->len - 1] == '\n')
		line->str[line->len - 1] = '\0';
	return(line->len > 0 ? 1 : 0); 
}

int		read_delim(t_line *line, char delim)
{
	line->len = getdelim(&line->str, &as_you_wish, delim, line->fd);
	if (line->len > 0 && line->str[line->len - 1] == delim)
		line->str[line->len - 1] = '\0';
	return(line->len > 0 ? 1 : 0); 
}

void	skip_read_line(t_line *l, int n)
{
	while (n-- > 0)
		if ((read_line(l)) <= 0)
		{
			printf("No more lines in file \"%s\".\n", l->filename);
			break;
		}
}

void	skip_read_delim(t_line *l, char delim, int n)
{
	while (n-- > 0)
		if ((read_delim(l, delim)) <= 0)
		{
			printf("No more lines in file \"%s\".\n", l->filename);
			break;
		}
}
