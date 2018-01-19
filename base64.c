/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:30:05 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/19 01:53:46 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

