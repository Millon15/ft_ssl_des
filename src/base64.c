/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/19 20:39:23 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	char	*decrypt_base64(void)
{
	return (NULL);
}

static	char	*encrypt_base64(char *line, size_t slen, size_t i, char res)
{
	char	st[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//	char	st[26 + 26 + 10 + 2 + 1];
	char	rem;
	char	*fin;
	size_t	remidner;

//	st = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	remidner = ((slen % 3) == 1 ? slen + 1 : slen + 2);
	slen = (remidner ? (slen + remidner) : slen) / 3 * 4 + 1;
	fin = (char *)malloc(sizeof(char) * slen);
	fin[slen - 1] = '\0';
	printf("%zu | %zu | %zu\n", i, slen, remidner);
	while (i < (slen - remidner))
	{
		res = line[i] >> 2;
		fin[i] = st[res];
		rem = line[i++] << 6;
		res = line[i] >> 4;
		fin[i] = st[res | rem];
		rem = line[i++] << 4;
		res = line[i] >> 2;
		fin[i] = st[res | rem];
		rem = line[i++] << 6;
		fin[i] = st[rem];
	}
	while (i < slen)
		fin[i++] = '=';
	return (fin);
}

int				put_base64(char **av, t_fl *fl)
{
	ssize_t		ret;
	char		*buf;
	t_b64		*fin;
	int			k[3];

	k[0] = fl->bufsize ? fl->bufsize : BUFF_SIZE;
	if ((k[1] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1 ||\
	(k[2] = fl->out ? open(fl->out, O_WRONLY) : 1) == -1)
		return (error(1, av, fl, 0));
	buf = (char *)malloc(sizeof(char) * (k[0] + 1));
	fin->res = (char *)malloc(sizeof(char) * ());
	while ((ret = read(k[1], buf, k[0])))
	{
		if (ret == -1)
			return (error(1, av, fl, 0));
		buf[ret] = '\0';
		fin = (fl->decrypt ? decrypt_base64() : encrypt_base64(buf, ft_strlen(buf), 0, 0));
		
		free(fin);
	}
	if (write(k[2], fin, ft_strlen(fin)) == -1)
		return (error(1, av, fl, 0));
	return (0);
}
