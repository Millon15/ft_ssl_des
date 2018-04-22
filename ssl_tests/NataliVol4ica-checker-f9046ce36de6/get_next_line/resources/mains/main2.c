/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:33:28 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/16 15:33:28 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../get_next_line.h"

#define LOG 0

void	do_print(int c, char *str)
{
	if (LOG)
		printf ("Func return %d.\nGNL is \"%s\"\n======== \n", c, str);
	else
		printf("%d\n%s\n", c, str);
}

int		main(void)
{
	char	*ans;
	int		c;
	int		fd;

	ans = NULL;
	c = 1;
	fd = 0;
	while ((c = get_next_line(fd, &ans) > 0))
		do_print(c, ans);
	printf("%d\n", c);
	close(fd);
	return (0);
}
