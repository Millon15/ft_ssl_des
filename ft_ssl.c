/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 00:39:08 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/27 15:49:28 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	void	fill_zeros(t_fl *fl)
{
	fl->encrypt = 0;
	fl->decrypt = 0;
	fl->base64 = 0;
	fl->bufs = 0;
	fl->in = 0;
	fl->out = 0;
}

static	int		read_command(char **av, t_fl *fl)
{
	if (!(ft_strcmp(av[1], "base64")))
		return ((fl->base64 = 1));
	return (-1);
}
static	int		put_enc(char **av, t_fl *fl)
{
	if (fl->base64)
		return (put_base64(av, fl));
	else
		return (-1);
}

static	int		read_args(char **av, t_fl *fl, unsigned int i)
{
	while (av[++i])
	{
		if ((!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")))\
		&& av[i + 1])
			fl->in = av[++i];
		else if ((!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o")))\
		&& av[i + 1])
			fl->out = av[++i];
		else if ((!(ft_strcmp(av[i], "-bufsize"))) && av[i + 1])
			fl->bufs = ft_atoi(av[++i]);
		else if (!(ft_strcmp(av[i], "-e")))
			fl->encrypt = 1;
		else if (!(ft_strcmp(av[i], "-d")))
			fl->decrypt = 1;
		else
			return (error(-1, av, fl, i));
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
	if (read_args(av, fl, 1) == -1 || put_enc(av, fl) == -1)
		return (-1);
	// printf("%-10p %-10u %-10u %-10u\n", fl, fl->encrypt, fl->decrypt, fl->base64);
	free(fl);
	return (0);
}
