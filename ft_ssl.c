/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 00:39:08 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/05 21:22:39 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static	void	fill_zeros(t_fl *fl)
{
	fl->encrypt = 0;
	fl->decrypt = 0;
	fl->base64 = 0;
	fl->des_ecb = 0;
	fl->des_cbc = 0;
	fl->des3 = 0;
	fl->des3_ecb = 0;
	fl->des3_cbc = 0;
	fl->cbc_mode = 0;
	fl->a = 0;
	fl->iv = 0;
	fl->bufs = 0;
	fl->in = 0;
	fl->out = 0;
	ft_bzero(fl->k, 49);
	ft_bzero(fl->iv_buf, 17);
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

static	void	stdin_reading(int ac, char **av, t_fl *fl)
{
	while (1)
	{
		write(1, "ft_SSL> ", 8);
		fill_zeros(fl);
		av = read_from_stdin(&ac);
		if ((read_command(ac, av, fl, 0)) != -1)
			return ;
	}
}

int				main(int ac, char **av)
{
	t_fl	*fl;

	fl = (t_fl *)malloc(sizeof(t_fl));
	fill_zeros(fl);
	if (ac == 1)
		stdin_reading(ac, av, fl);
	else
		read_command(ac, av, fl, 1);
	free(fl);
	return (0);
}
