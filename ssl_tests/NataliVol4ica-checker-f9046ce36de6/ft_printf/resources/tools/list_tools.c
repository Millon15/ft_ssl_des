
#include <stdlib.h>
#include "tools.h"

t_list	*lst_new(char *str)
{
	t_list	*l;

	if (!(l = (t_list*)malloc(sizeof(t_list)))) bad_malloc();
	l->str = ft_strdup(str);
	l->next = NULL;
	return (l);
}

void	lst_push_back(t_list **list, t_list *elem)
{
	t_list	*l;

	if (!list) bad_input();
	if (!*list)
	{
		*list = elem;
		return ;
	}
	l = *list;
	while (l->next)
		l = l->next;
	l->next = elem;
}
