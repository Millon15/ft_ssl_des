/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:03:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/27 14:31:45 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	int		put_endres(char **av, t_fl *fl)
{
	if (fl->base64)
		return (put_base64(av, fl, 0));
	else if (fl->des_ecb || fl->des_cbc)
		return (put_des(av, fl, 0));
	return (-1);
}

static	int		check_args(int ac, char **av, t_fl *fl, int i_buf)
{
	char		buf[17];
	ssize_t		ret;

	if (!((fl->k)[0]) && fl->des_ecb)
	{
		ft_putstr("enter des-ecb encryption key: ");
		read(0, fl->k, 16);
		ft_putstr("Verifying - enter des-ecb encryption key: ");
		ret = read(0, buf, 16);
		buf[ret] = '\0';
		if (ft_strncmp(fl->k, buf, 16))
			return ((error(99, av, NULL, i_buf)));
		ret = 0;
		while (!(ft_iswhitespace((fl->k)[ret])))
			ret++;
		(fl->k)[ret] = '\0';
	}
	put_endres(av, fl);
	return (0);
}

static	int		help_read_args(int ac, char **av, t_fl *fl, int i)
{
	if (!(ft_strcmp(av[i], "-e")))
		return ((fl->encrypt = 1));
	else if (!(ft_strcmp(av[i], "-d")))
		return ((fl->decrypt = 1));
	else if (!(ft_strcmp(av[i], "-a")))
		return ((fl->a = 1));
	return (-1);
}

static	int		read_args(int ac, char **av, t_fl *fl, int i)
{
	int		i_buf;

	i_buf = i;
	while (av[++i])
	{
		if ((!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")) ||\
		!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o")) ||\
		!(ft_strcmp(av[i], "-k")) || !(ft_strcmp(av[i], "-K")) ||\
		!(ft_strcmp(av[i], "-iv")) || !(ft_strcmp(av[i], "-v")) ||\
		!(ft_strcmp(av[i], "-bufsize"))) && !av[i + 1])
			return ((error(ac, av, (char *)1, i)));
		else if (!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")))
			fl->in = av[++i];
		else if (!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o")))
			fl->out = av[++i];
		else if (!(ft_strcmp(av[i], "-k")) || !(ft_strcmp(av[i], "-K")))
			ft_memcpy(fl->k, av[++i], 16);
		else if (!(ft_strcmp(av[i], "-iv")) || !(ft_strcmp(av[i], "-v")))
			ft_memcpy(fl->iv_buf, av[++i], 16);
		else if (!(ft_strcmp(av[i], "-bufsize")))
			fl->bufs = ft_atoi(av[++i]);
		else if ((help_read_args(ac, av, fl, i)) == -1)
			return ((error(ac, av, NULL, i)));
	}
	return (check_args(ac, av, fl, i_buf));
}

int				read_command(int ac, char **av, t_fl *fl, int i)
{
	if (!(ft_strcmp(av[i], "base64")))
		fl->base64 = 1;
	else if (!(ft_strcmp(av[i], "des")) || !(ft_strcmp(av[i], "des-ecb")))
		fl->des_ecb = 1;
	else if (!(ft_strcmp(av[i], "des-cbc")))
		fl->des_cbc = 1;
	else
		return ((error(2, av, NULL, i)));
	return (read_args(ac, av, fl, i));
}
