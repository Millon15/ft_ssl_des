/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 00:39:08 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/19 02:19:38 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	int		error(int ac, char **av, t_fl *fl, unsigned int i)
{
	if (ac == 1)
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	else if (ac >= 2)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[1]);
		ft_putstr("' is an invalid command.\nStandard commands:\n\n\
		Message Digest commands:\n\nCipher commands:\nbase64\n");
		//des\ndes-ecb\ndes-cbc\n");
	}
	else if (ac == -1)
	{
		ft_putstr("unknown option '");
		ft_putstr(av[i]);
		ft_putstr("options are\n-in <file>\tinput file\n\
		-out <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n\
		Cipher Types\ndes\t\tdes-ecb\t\tdes-cbc\n");
	}
	else if (ac == -2)
		ft_putstr("options are\n-in <file>\tinput file\n\
		-out <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n\
		Cipher Types\ndes\t\tdes-ecb\t\tdes-cbc\n");
	free(fl);
	return (-1);
}

static	void	fill_zeros(t_fl *fl)
{
	fl->encrypt = 0;
	fl->decrypt = 0;
	fl->base64 = 0;
	fl->in = 0;
	fl->out = 0;
}

static	int		read_command(char **av, t_fl *fl)
{
	if (!(ft_strcmp(av[1], "base64")))
		return ((fl->base64 = 1));
	return (-1);
}

int		read_args(char **av, t_fl *fl)
{
	unsigned int	i;

	i = 1;
	while (av[++i])
	{
		if (av[i][0] == '-')
		{
			if (ft_strcmp(av[i], "-in"))
				fl->in = i + 1;
			else if (ft_strcmp(av[i], "-out"))
				fl->out = i + 1;
			else if (ft_strcmp(av[i], "-e"))
				fl->encrypt = 1;
			else if (ft_strcmp(av[i], "-d"))
				fl->decrypt = 1;
			else
				return (error(-1, av, fl, i));
		}
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_fl	*fl;

	fl = (t_fl *)malloc(sizeof(t_fl));
	fill_zeros(fl);
	if (ac == 1 || (read_command(av, fl) == -1))
		return (error(ac, av, fl, 0));
	if (read_args(av, fl) == -1)
		return (-1);
	printf("%-10p %-10u %-10u %-10u", fl, fl->encrypt, fl->decrypt, fl->base64);
	free(fl);
	return (0);
}
