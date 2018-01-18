/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/18 22:22:24 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"
#include <stdio.h>

static	void	crypt_base64(char *line, size_t slen, size_t i, char res)
{
	size_t	remidner;
	char	rem;
	char	*fin;
//	char	st[26 + 26 + 10 + 2 + 1];
	char	st[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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
	// printf("%s\n", fin);
	ft_printf("%s\n", fin);
	free(fin);
}

static	int		fill_flags(char **av, t_base64 *b64, int *fd)
{
	size_t	i;
	char	*buf;

	i = 0;
	buf = NULL;
	if (av[1][0] == '-' && (*fd = 1))
		buf = av[1];
	else if (av[2][0] == '-' && (*fd = 2))
		buf = av[2];
	if (!buf)
		return (-1);
	while (buf[i++])
	{
		if (i == 2 && !b64->crypt && !b64->decrypt)
			return (-1);
		else if (i == 2)
			break ;
		if (buf[i] == 'c')
			b64->crypt = 1;
		else if (buf[i] == 'd')
			b64->decrypt = 1;
	}
	return (0);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*line;
	t_base64	*b64;

	if (ac > 3)
		return (-1);
	b64 = (t_base64 *)malloc(sizeof(t_base64));
	b64->crypt = 0;
	b64->decrypt = 0;
	if (ac == 1)
		fd = 0;
	else if (ac == 2 && (b64->crypt = 1))
		fd = open(av[1], O_RDONLY);
	else if (ac == 3)
	{
		if (fill_flags(av, b64, &fd) == -1)
			return (-1);
		fd = open(av[fd], O_RDONLY);
	}
	if (get_next_line(fd, &line) == -1)
		return (-1);
	printf("%s\n%d | %d\n", line, b64->crypt, b64->decrypt);
	b64->crypt ? crypt_base64(line, ft_strlen(line), 0, 0) : 0;//encrypt_base64(line);
	free(b64);
	close(fd);
	return (0);
}
