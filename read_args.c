/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:03:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/01 16:09:19 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	int		put_endres(char **av, t_fl *fl)
{
	if (fl->base64)
		return (put_base64(av, fl, 0));
	// else if (fl->des_ecb)
	// 	return (put_des_ecb(av, fl, 0));
	return (-1);
}

static	int		help_read_args(int ac, char **av, t_fl *fl, int i)
{
	if (!(ft_strcmp(av[i], "base64")))
		return ((fl->base64 = 1));
	else if (!(ft_strcmp(av[i], "des")) || !(ft_strcmp(av[i], "des-ecb")))
		return ((fl->des_ecb = 1));
	else if (!(ft_strcmp(av[i], "-e")))
		return ((fl->encrypt = 1));
	else if (!(ft_strcmp(av[i], "-d")))
		return ((fl->decrypt = 1));
	else if (!(ft_strcmp(av[i], "-a")))
		return ((fl->a = 1));
	return (0);
}

int				read_args(int ac, char **av, t_fl *fl, int i)
{
	while (av[++i])
	{
		if ((!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")) ||\
		!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o")) ||\
		!(ft_strcmp(av[i], "-k")) || !(ft_strcmp(av[i], "-K"))) && !av[i + 1])
			return ((error(ac, av, (char *)1, i)));
		else if (!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")))
			fl->in = av[++i];
		else if (!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o")))
			fl->out = av[++i];
		else if (!(ft_strcmp(av[i], "-k")) || !(ft_strcmp(av[i], "-K")))
			fl->k = av[++i];
		else if ((!(ft_strcmp(av[i], "-bufsize"))) && av[i + 1])
			fl->bufs = ft_atoi(av[++i]);
		else if (!(help_read_args(ac, av, fl, i)))
			return ((error(ac, av, NULL, i)));
	}
	return ((put_endres(av, fl)));
}