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

int		main(int ac, char **av)
{
	char	*ans;
	int		c;
	int		fd1, fd2, fd3;

	ans = NULL;
	c = 1;
	if (ac >= 4)
	{
		fd1 = open(av[1], O_RDONLY);
		fd2 = open(av[2], O_RDONLY);
		fd3 = open(av[3], O_RDONLY);
		if (fd1 >= 0 && fd2 >= 0 && fd3 >= 0)
		{
			if (LOG)
				printf("\n""\x1b[32m""File name = \"%s\"\n\n""\x1b[0m", av[1]);
			c = get_next_line(fd1, &ans);
			do_print(c, ans);
			c = get_next_line(fd1, &ans);
			do_print(c, ans);
			c = get_next_line(fd2, &ans);
			do_print(c, ans);
			c = get_next_line(fd3, &ans);
			do_print(c, ans);
			c = get_next_line(fd2, &ans);
			do_print(c, ans);
			c = get_next_line(fd1, &ans);
			do_print(c, ans);
			c = get_next_line(fd3, &ans);
			do_print(c, ans);
			c = get_next_line(fd2, &ans);
			do_print(c, ans);
			c = get_next_line(fd1, &ans);
			printf("%d\n", c);
			c = get_next_line(fd3, &ans);
			do_print(c, ans);
			c = get_next_line(fd2, &ans);
			printf("%d\n", c);
			c = get_next_line(fd3, &ans);
			printf("%d\n", c);
		}
		close(fd1);
		close(fd2);
		close(fd3);
	}
	return (0);
}
