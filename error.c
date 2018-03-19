/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:09:45 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/18 18:24:05 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	void	help(int ac, char **av, char *str, int i)
{
	if (ac > 2)
	{
		if (!str)
			ft_putstr("unknown option '");
		else if ((unsigned long)str == 1)
			ft_putstr("missing argument for '");
		if ((unsigned long)str == 1 || !str)
			ft_putstr(av[i]);
		ft_putstr("'\nusage: ft_ssl command [command opts] [command args]\n\n"
		"Valid command opts values:\n"
		"-in or -i <file>\tInput file to read from (default stdin)\n"
		"-out or -o <file>\tOutput file to write to (default stdout)\n"
		"-bufsize <size>\t\tSpecify the buffer size to use for I/O\n"
		"-e\t\t\tEncrypt the input data\n""-d\t\t\tDencrypt the input data\n"
		"-k <key>\t\tkey for des is the next argument\n""\nCipher commands:"
		"\nbase64\ndes\ndes-ecb\ndes-cbc\ndes3\ndes3-ecb\ndes3-cbc\n");
	}
}

int				error(int ac, char **av, char *str, int i)
{
	if (ac == -1)
	{
		if (str)
			ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (ac == 1)
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	else if (ac == 2)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[i]);
		ft_putstr("' is an invalid command.\n\nStandard commands:\n\n"
		"Message Digest commands:\n\nCipher commands:\nbase64\n"
		"des\ndes-ecb\ndes-cbc\ndes3\ndes3-ecb\ndes3-cbc\n");
	}
	else if (ac == -2)
		ft_putstr("Verify failure\nbad input read\n");
	else
		help(ac, av, str, i);
	return (-1);
}
