/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 21:41:18 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/07 22:29:26 by vbrazas          ###   ########.fr       */
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

void					make_subkey(t_fl *fl)
{
	ssize_t				i;

	i = 0;
	while (i < 48)
	{
		ft_strncpy((fl->sub_k)[(i / 16)], (fl->k + i), 16);
		(fl->sub_k)[(i / 16)][16] = '\0';
		i += 16;
	}
}

unsigned long			des3_algorythm(unsigned long buf, t_fl *fl)
{
	unsigned long		res[3];
	char				k_buf[49];

	ft_strcpy(k_buf, fl->k);
	ft_strcpy(fl->k, (fl->sub_k)[0]);
	res[0] = endecrypt_des(buf, fl);
	ft_strcpy(fl->k, (fl->sub_k)[1]);
	
	
	res[1] = endecrypt_des(res[0], fl);
	ft_strcpy(fl->k, (fl->sub_k)[2]);
	res[2] = endecrypt_des(res[1], fl);
	ft_strcpy(fl->k, k_buf);
	return (res[2]);
}
