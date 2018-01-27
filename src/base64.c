/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/27 17:05:58 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	char	*decrypt_base64(void)
{
	return (NULL);
}

static	char	*encrypt_base64(char *line, size_t ln, size_t i, size_t j)
{
	const	char	st[] =\
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned char	res;
	unsigned char	rem;
	char			*fin;

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

int				put_base64(char **av, t_fl *fl)
{
	ssize_t		ret;
	char		*buf;
	char		*r;
	int			k[2];
	int			bfs;

	bfs = (fl->bufs ? fl->bufs : BUFF_SIZE);
	if ((k[0] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1 ||\
	(k[1] = fl->out ? open(fl->out, O_WRONLY) : 1) == -1)
		return (error(1, av, fl, 0));
	buf = (char *)malloc(sizeof(char) * (bfs + 1));
	while ((ret = read(k[0], buf, bfs)))
	{
		if (ret == -1)
			return (error(1, av, fl, 0));
		buf[ret] = '\0';
		r = (fl->decrypt ? decrypt_base64() : encrypt_base64(buf, ret , 0, 0));
		if ((write(k[1], r, ft_strlen(r))) == -1)
			return (error(1, av, fl, 0));
		free(r);
	}
	write(1, "\n", 1);
	free(buf);
	return (0);
}
