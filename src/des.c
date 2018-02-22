/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:16:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/22 16:46:40 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	unsigned long	to_digit(char *s)
{
	unsigned long	res;
	int				i;
	int				l;
	int				k;

	i = 0;
	k = 0;
	l = 0;
	res = 0;
	while (l != 8)
	{
		res <<= 8;
		if (!s[i] && !k)
			k = 8 - l;
		res |= (s[i] ? s[i++] : k);
		l++;
	}
	// printf("%s ", ft_utoa_base(res, 16));
	return (res);
}

char					*from_digit(unsigned long res)
{
	char	*s;
	int		a;
	int		i;

	// printf("%s ", ft_utoa_base(res, 16));
	s = (char *)malloc(sizeof(char) * 9);
	i = 0;
	a = 0;
	while (a != 64)
	{
		s[i++] = (res << a) >> 56;
		a += 8;
	}
	return (s);
}

static	char			*pre_encrypt_des_ecb(char *line, t_fl *fl)
{
	char		*line2;
	char		*line2_buf;
	char		*buf;
	int			l;
	int			i;

	l = ft_strlen(line);
	l = !(l % 8) ? (l + 8) : l;
	line2 = (char *)malloc(sizeof(char) * (l + 1));
	line2[l] = '\0';
	line2 = encrypt_des_ecb(to_digit(line), fl);
	i = 8;
	while ((l - i) > 0)
	{
		buf = encrypt_des_ecb(to_digit(line + i), fl);
		line2_buf = line2;
		line2 = ft_strjoin(line2, buf);
		free(line2_buf);
		free(buf);
		i += 8;
	}
	// printf("\n\n");
	return (line2);
}

int						put_des_ecb(char **av, t_fl *fl, ssize_t ret)
{
	char		*r[3];
	int			k[3];

	if ((k[0] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1)
		return (error(-1, av, fl->in, 0));
	if ((k[1] = fl->out ? open(fl->out, O_WRONLY) : 1) == -1)
		return (error(-1, av, fl->out, 0));
	k[2] = (fl->bufs ? fl->bufs : BUFF_SIZE);
	r[0] = (char *)malloc(sizeof(char) * (k[2] + 1));
	r[1] = (char *)ft_memalloc(sizeof(char) * 1);
	while ((ret = read(k[0], r[0], k[2])))
	{
		r[0][ret] = '\0';
		r[2] = r[1];
		r[1] = ft_strjoin(r[0], r[1]);
		free(r[2]);
	}
	r[2] = (fl->decrypt ? decrypt_des_ecb(r[1], fl)\
	: pre_encrypt_des_ecb(r[1], fl));
	fl->a ? ft_putstr_fd(encrypt_base64(r[2], ft_strlen(r[2]), 0, 0), k[1])\
	: ft_putstr_fd(r[2], k[1]);
	free(r[2]);
	free(r[1]);
	free(r[0]);
	return (0);
}
