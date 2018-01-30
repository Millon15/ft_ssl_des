/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 00:39:08 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/30 21:32:12 by vbrazas          ###   ########.fr       */
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

static	int		put_endres(char **av, t_fl *fl)
{
	if (fl->base64)
		return (put_base64(av, fl, 0));
	return (-1);
}

static	int		read_args(int ac, char **av, t_fl *fl, int i)
{
	while (av[++i])
	{
		if (!(ft_strcmp(av[i], "base64")))
			fl->base64 = 1;
		else if ((!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")) ||\
		!(ft_strcmp(av[i], "-out")) || !(ft_strcmp(av[i], "-o"))) && !av[i + 1])
			return (error(ac, av, (char *)1, i));
		else if ((!(ft_strcmp(av[i], "-in")) || !(ft_strcmp(av[i], "-i")))\
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
			return (error(ac, av, NULL, i));
	}
	return (0);
}

static	char	**read_from_stdin(int *ac)
{
	char		**av;
	char		*buf;
	char		*buf_buf;
	size_t		i;
	ssize_t		ret;

	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	ret = read(1, buf, BUFF_SIZE);
	buf[ret] = '\0';
	buf_buf = buf;
	buf = ft_strtrim(buf);
	free(buf_buf);
	av = ft_strsplit(buf, ' ');
	free(buf);
	i = 0;
	while (av[i])
		i++;
	*ac = i + 1;
	return (av);
}

static	void	ac1(int ac, char **av, t_fl *fl)
{
	while (1)
	{
		write(1, "ft_SSL> ", 8);
		fill_zeros(fl);
		av = read_from_stdin(&ac);
		if ((read_args(ac, av, fl, -1)) != -1)
			if ((put_endres(av, fl)) == 0)
				return ;
	}
}

int				main(int ac, char **av)
{
	t_fl	*fl;

	fl = (t_fl *)malloc(sizeof(t_fl));
	fill_zeros(fl);
	if (ac == 1)
		ac1(ac, av, fl);
	else if ((read_args(ac, av, fl, 0)) != -1)
		put_endres(av, fl);
	free(fl);
	return (0);
}
