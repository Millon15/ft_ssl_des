/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/27 14:34:43 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	char	*decrypt_base64(void)
{
	return (NULL);
}

static	char	*encrypt_base64(char *line, size_t slen, size_t i, size_t j)
{
	const	char	st[] =\
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned char	res;
	unsigned char	rem;
	char			*fin;

	// printf("%c\n", st[60]);
	// printf("slen1 = %zu\n", slen);
	slen = (((slen % 3) && (slen % 3) == 2) ? (slen + 1) : (slen + 2)) / 3 * 4 + 1;
	fin = (char *)malloc(sizeof(char) * slen);
	fin[--slen] = '\0';
	// printf("slen2 = %zu\n", slen);
	while (i < slen)
	{
		res = (line[j] ? (line[j] >> 2) : 65);
		fin[i++] = st[res];
		// printf("%c | %d\n", fin[i - 1], res);
		rem = (line[j] ? (line[j++] << 6) : 65);
		res = (line[j] ? ((line[j] >> 4) << 2) : 65);
		fin[i++] = st[(res | rem) >> 2];
		// printf("%c | %d\n", fin[i - 1], (res | rem) >> 2);
		rem = (line[j] ? (line[j++] << 4) : 65);
		res = (line[j] ? ((line[j] >> 6) << 2): 65);
		fin[i++] = (line[j] ? (st[((res | rem) >> 2)]) : '=');
		// printf("%c | %d\n", fin[i - 1], (res | rem) >> 2);
		rem = (line[j] ? (line[j++] << 2) : 65);
		fin[i++] = (line[j] ? (st[rem >> 2]) : '=');
		// printf("%c | %d\n", fin[i - 1], rem >> 2);
	}
	// printf("%s | %zu | %zu\n", fin, i, j);
	return (fin);
}

int				put_base64(char **av, t_fl *fl)
{
	ssize_t		ret;
	char		*buf;
	char		*r;
	int			k[2];

	if ((k[0] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1 ||\
	(k[1] = fl->out ? open(fl->out, O_WRONLY) : 1) == -1)
		return (error(1, av, fl, 0));
	buf = (char *)malloc(sizeof(char) * 65);
	while ((ret = read(k[0], buf, 64)))
	{
		if (ret == -1)
			return (error(1, av, fl, 0));
		buf[ret] = '\0';
		r = (fl->decrypt ? decrypt_base64() : encrypt_base64(buf, ret , 0, 0));
		if ((write(k[1], r, ft_strlen(r)) == -1) ||\
		(write(k[1], "\n", 1) == -1))
			return (error(1, av, fl, 0));
		free(r);
	}
	free(buf);
	return (0);
}
