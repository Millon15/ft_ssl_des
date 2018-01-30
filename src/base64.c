/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/30 20:39:14 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	unsigned int	find_num(char a)
{
	unsigned int	i;
	const	char	st[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

	"abcdefghijklmnopqrstuvwxyz0123456789+/";
	i = 0;
	if (a == '=')
		return (0);
	while (a != st[i])
		i++;
	return (i);
}

static	char			*decrypt_base64(char *line, size_t ln,\
size_t i, size_t j)
{
	unsigned char	res;
	unsigned char	rem;
	char			*fin;

	while (line[i])
		if (line[i++] == '\n')
			j++;
	ln = !((ln - j) % 4) ? ((i - j) / 4 * 3) : 0;
	fin = (char *)malloc(sizeof(char) * (ln + 1));
	i = 0;
	j = 0;
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

static	char			*encrypt_base64(char *line, size_t ln,\
size_t i, size_t j)
{
	unsigned char	res;
	unsigned char	rem;
	char			*fin;
	const	char	st[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

	"abcdefghijklmnopqrstuvwxyz0123456789+/";
	ln = ((((ln % 3) && (ln % 3) == 2) ? (ln + 1) : (ln + 2)) / 3 * 4);
	fin = (char *)malloc(sizeof(char) * (ln + ln / 64 + 1));
	while (i < ln)
	{
		res = line[j] >> 2;
		fin[i++] = st[res];
		rem = line[j++] << 6;
		res = (line[j] >> 4) << 2;
		fin[i++] = st[(res | rem) >> 2];
		rem = line[j++] << 4;
		res = (line[j] ? ((line[j] >> 6) << 2) : 0);
		fin[i++] = ((line[j] || res || rem) ? (st[((res | rem) >> 2)]) : '=');
		rem = (line[j] ? (line[j++] << 2) : 0);
		fin[i++] = ((line[j] || res || rem) ? (st[rem >> 2]) : '=');
		if (!(i % 64))
			fin[i++] = '\n';
	}
	fin[i] = '\0';
	return (fin);
}

int						put_base64(char **av, t_fl *fl, ssize_t ret)
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
		r[1] = ft_strjoin(r[1], r[0]);
		free(r[2]);
	}
	r[1] = (fl->decrypt ? decrypt_base64(r[1], ft_strlen(r[1]), 0, 0) :\
		encrypt_base64(r[1], ft_strlen(r[1]), 0, 0));
	fl->decrypt ? ft_putstr_fd(r[1], k[1]) : ft_putendl_fd(r[1], k[1]);
	free(r[1]);
	free(r[0]);
	return (0);
}
