/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:03:55 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/09 19:11:19 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	int		put_endres(char **av, t_fl *fl)
{
	char		buf[17];
	ssize_t		ret;

	if (!((fl->iv_buf)[0]) && fl->cbc_mode)
	{
		ft_putstr("enter des initial vector: ");
		ret = read(0, fl->iv_buf, 17);
		(fl->iv_buf)[ret - 1] = '\0';
		ft_putstr("Verifying - enter again des initial vector: ");
		ret = read(0, buf, 17);
		buf[ret - 1] = '\0';
		if (ft_strncmp(fl->iv_buf, buf, 17))
			return ((error(-2, av, NULL, 0)));
	}
	if (fl->base64)
		return (put_base64(av, fl, 0, 0));
	else if (fl->des_ecb || fl->des_cbc || fl->des3)
		return (put_des(av, fl, 0, 0));
	return (-1);
}

static	int		check_args(int ac, char **av, t_fl *fl)
{
	char		buf[17];
	ssize_t		ret;

	if (!((fl->k)[0]) && fl->cbc_mode)
	{
		ft_putstr("enter des encryption key: ");
		ret = read(0, fl->k, (fl->des3 ? 49 : 17));
		(fl->k)[ret - 1] = '\0';
		ft_putstr("Verifying - enter again des encryption key: ");
		ret = read(0, buf, (fl->des3 ? 49 : 17));
		buf[ret - 1] = '\0';
		if (ft_strncmp(fl->k, buf, (fl->des3 ? 49 : 17)))
			return ((error(-2, av, NULL, 0)));
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
	else if (!(ft_strcmp(av[i], "-bufsize")))
		fl->bufs = ft_atoi(av[++i]);
	else if (!(ft_strcmp(av[i], "-a")) || !(ft_strcmp(av[i], "-base64")))
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
		!(ft_strcmp(av[i], "-bufsize"))) && \
		(av[i + 1][0] == '-' || !(av[i + 1])))
			return ((error(ac, av, (char *)1, i)));
		else if (!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")))
			fl->in = av[++i];
		else if (!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o")))
			fl->out = av[++i];
		else if (!(ft_strcmp(av[i], "-k")) || !(ft_strcmp(av[i], "-K")))
			ft_strncpy(fl->k, av[++i], (fl->des3 ? 48 : 16));
		else if (!(ft_strcmp(av[i], "-iv")) || !(ft_strcmp(av[i], "-v")))
			ft_strncpy(fl->iv_buf, av[++i], 16);
		else if ((help_read_args(ac, av, fl, i)) == -1)
			return ((error(ac, av, NULL, i)));
	}
	return (check_args(ac, av, fl));
}

int				read_command(int ac, char **av, t_fl *fl, int i)
{
	if (!(ft_strcmp(av[i], "base64")))
		fl->base64 = 1;
	else if (!(ft_strcmp(av[i], "des")) || !(ft_strcmp(av[i], "des-ecb")))
		fl->des_ecb = 1;
	else if (!(ft_strcmp(av[i], "des-cbc")))
		fl->des_cbc = 1;
	else if (!(ft_strcmp(av[i], "des3")) || !(ft_strcmp(av[i], "des-ede3-cbc")))
		fl->des3_cbc = 1;
	else if (!(ft_strcmp(av[i], "des-ede3")))
		fl->des3_ecb = 1;
	else
		return ((error(2, av, NULL, i)));
	if (fl->des3_ecb || fl->des3_cbc)
		fl->des3 = 1;
	if (fl->des3_cbc || fl->des_cbc)
		fl->cbc_mode = 1;
	return (read_args(ac, av, fl, i));
}
