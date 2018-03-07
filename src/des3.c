/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:41:18 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/07 21:18:47 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

char					*from_digit(unsigned long res)
{
	char	*s;
	int		a;
	int		i;

	s = (char *)malloc(sizeof(char) * 9);
	i = 0;
	a = 0;
	while (a != 64)
	{
		s[i++] = (res << a) >> 56;
		a += 8;
	}
	s[8] = '\0';
	return (s);
}

unsigned long			des3_algorythm(unsigned long buf, t_fl *fl)
{
	unsigned long		res[3];
	char				k_buf[49];
	char				k[3][17];
	ssize_t				i;

	i = 0;
	ft_strcpy(k_buf, fl->k);
	while (i < 48)
	{
		ft_strncpy(k[(i / 16)], (fl->k + i), 16);
		k[(i / 16)][16] = '\0';
		i += 16;
	}
	ft_strcpy(fl->k, k[0]);
	res[0] = endecrypt_des(buf, fl);
	ft_strcpy(fl->k, k[1]);
	fl->decrypt = fl->decrypt ? 0 : 1;
	res[1] = endecrypt_des(res[0], fl);
	ft_strcpy(fl->k, k[2]);
	fl->decrypt = fl->decrypt ? 1 : 0;
	res[2] = endecrypt_des(res[1], fl);
	ft_strcpy(fl->k, k_buf);
	return (res[2]);
}
