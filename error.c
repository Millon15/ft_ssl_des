/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:09:45 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/28 15:38:24 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	void	help(int ac, char **av, char *str, int i)
{
	if (ac > 2 && ac != 99)
	{
		if (!str)
			ft_putstr("unknown option '");
		else if ((unsigned long)str == 1)
			ft_putstr("missing file argument for '");
		if ((unsigned long)str == 2 || (unsigned long)str == 1 || !str)
			ft_putstr(av[i]);
		ft_putstr("'\nusage: ft_ssl command [command opts] [command args]\n\n"
		"Valid command opts values:\n\n"
		"-in or -i <file>\tInput file to read from (default stdin)\n"
		"-out or -o <file>\tOutput file to write to (default stdout)\n"
		"-bufsize <size>\t\tSpecify the buffer size to use for I/O\n"
		"-e\t\t\tEncrypt the input data\n""-d\t\t\tDencrypt the input data\n"
		"-k <key>\t\t\tkey for des is the next argument\n");
	}
}

int				error(int ac, char **av, char *str, int i)
{
	if (ac == -1)
	{
		if (str)
			ft_putstr(str);
		ft_putstr(": No such file or directory\n");
	}
	else if (ac == 1)
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	else if (ac == 2)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[i]);
		ft_putstr("' is an invalid command.\n\nStandard commands:\n\n"
		"Message Digest commands:\n\nCipher commands:\nbase64\n"
		"des\ndes-ecb\ndes-cbc\n");
	}
	else if (ac == -2)
		ft_putstr("Verify failure\nbad input read\n");
	else
		help(ac, av, str, i);
	return (-1);
}
