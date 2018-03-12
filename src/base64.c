/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/12 19:24:41 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "permutations.h"

#include <stdio.h>

static	unsigned char	find_num(char a)
{
	unsigned char	i;

	i = 0;
	if (a == '=')
		return (0);
	while (g_st[i] && a != g_st[i])
		i++;
	return (i);
}

char					*decrypt_base64(char *line, ssize_t ln, \
						size_t i, ssize_t j)
{
	unsigned char	res;
	unsigned char	rem;
	char			*fin;

	ln = (ln / 4 * 3) - ((ln / 4 * 3) / 64);
	fin = (char *)malloc(sizeof(char) * (ln + 1));
	while (j < ln)
	{
		res = find_num(line[i++]);
		rem = find_num(line[i++]);
		fin[j++] = (res << 2) | (rem >> 4);
		res = find_num(line[i++]);
		fin[j++] = (rem << 4) | (res >> 2);
		rem = find_num(line[i++]);
		fin[j++] = (res << 6) | rem;
		if (!(i % 64))
			i++;
	}
	fin[j] = '\0';
	return (fin);
}

char					*encrypt_base64(char *line, ssize_t ln, size_t i, \
						ssize_t j)
{
	unsigned char	re[2];
	char			*fin;
	size_t			tmp[2];

	tmp[0] = 0;
	tmp[1] = ((ln + 2) / 3 * 4) + ((ln + 2) / 3 * 4) / 64;
	fin = (char *)malloc(sizeof(char) * (tmp[1] + 1));
	while (i < tmp[1])
	{
		fin[i++] = g_st[(unsigned char)line[j] >> 2];
		re[0] = (unsigned char)line[j++] << 6;
		re[1] = ((unsigned char)line[j] >> 4) << 2;
		fin[i++] = g_st[((re[1] | re[0]) >> 2)];
		re[0] = (unsigned char)line[j++] << 4;
		re[1] = (j < ln) ? (((unsigned char)line[j] >> 6) << 2) : 0;
		fin[i++] = (re[1] || re[0] || (j < (ln - 1))) ? \
		(g_st[((re[1] | re[0]) >> 2)]) : '=';
		re[0] = (j < ln) ? ((unsigned char)line[j++] << 2) : 0;
		fin[i++] = (re[1] || re[0] || (j < (ln - 1))) ? \
		(g_st[(re[0] >> 2)]) : '=';
		if (!((i - tmp[0]) % 64) && ++tmp[0])
			fin[i++] = '\n';
	}
	fin[!((i - tmp[0]) % 64) ? (i - 1) : i] = '\0';
	return (fin);
}

static	int				help_put_base64(char *r[])
{
	free(r[2]);
	free(r[1]);
	free(r[0]);
	return (0);
}

int						put_base64(char **av, t_fl *fl, ssize_t ret, ssize_t l)
{
	char		*r[3];
	int			k[3];

	if ((k[0] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1)
		return (error(-1, av, fl->in, 0));
	if ((k[1] = fl->out ? open(fl->out, O_WRONLY | \
	O_CREAT | O_TRUNC, 0666) : 1) == -1)
		return (error(-1, av, fl->out, 0));
	k[2] = (fl->bufs ? fl->bufs : BUFF_SIZE);
	r[0] = (char *)malloc(sizeof(char) * (k[2] + 1));
	r[1] = (char *)ft_memalloc(sizeof(char) * 1);
	while ((ret = read(k[0], r[0], k[2])))
	{
		r[2] = r[1];
		r[1] = ft_strnjoin(r[1], r[0], l, ret);
		free(r[2]);
		l += ret;
	}
	r[2] = (fl->decrypt ? decrypt_base64(r[1], l, 0, 0) : \
	encrypt_base64(r[1], l + 2, 0, 0));
	l = fl->decrypt ? (l / 4 * 3 - (l / 4 * 3) / 64) : \
	((l + 2) / 3 * 4 + ((l + 2) / 3 * 4) / 64);
	fl->decrypt ? ft_putnstr_fd(r[2], k[1], l) : ft_putnendl_fd(r[2], k[1], l);
	return (help_put_base64(r));
}
