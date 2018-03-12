/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:41:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/07 22:11:18 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "permutations.h"

static	void			shift_keys(unsigned long c[], unsigned long d[])
{
	int					i;
	unsigned long		tmp[2];

	i = 0;
	while (i < 16)
	{
		tmp[0] = (c[i] << g_key_shift[i]) >> 28;
		tmp[1] = (d[i] << g_key_shift[i]) >> 28;
		c[i + 1] = tmp[0] | (c[i] << ((36 + g_key_shift[i])) >> 36);
		d[i + 1] = tmp[1] | (d[i] << ((36 + g_key_shift[i])) >> 36);
		i++;
	}
}

static	unsigned long	uni_permut(unsigned long k0, unsigned char perm[], \
						int end_len, int start_len)
{
	int					i;
	unsigned long		tmp;
	unsigned long		k1;

	i = 0;
	k1 = 0;
	while (i < end_len)
	{
		tmp = (k0 >> (start_len - perm[i++])) & 1;
		k1 <<= 1;
		k1 += tmp;
	}
	return (k1);
}

static	unsigned long	f(unsigned long text, unsigned long ki)
{
	unsigned long		l[8];
	unsigned long		res[2];
	int					a;
	int					b;
	int					c;

	res[0] = uni_permut(text, g_expand_permutation, 48, 32);
	res[0] = (res[0] ^ ki) << 16;
	a = -1;
	res[1] = 0;
	while (++a < 8)
	{
		l[a] = ((res[0] << (6 * a)) >> (6 * 7)) >> 16;
		b = ((l[a] << 63) >> 63) | (((l[a] >> 5) << 63) >> 62);
		c = ((l[a] >> 1) << 60) >> 60;
		res[1] |= (g_sboxes[a][b][c] << (4 * (7 - a)));
	}
	res[0] = uni_permut(res[1], g_pbox_permutation, 32, 32);
	return (res[0]);
}

unsigned long			endecrypt_des(unsigned long buf, t_fl *fl)
{
	unsigned long		i;
	unsigned long		m[17];
	unsigned long		k[17];
	unsigned long		l[17];
	unsigned long		r[17];

	k[0] = uni_permut(ft_atou_base(fl->k, 16), g_key_permutation_1, 56, 64);
	l[0] = (k[0] >> 28);
	r[0] = (k[0] << 36) >> 36;
	shift_keys(l, r);
	i = 0;
	while (i++ < 16)
		k[i] = uni_permut(((l[i] << 28) | r[i]), g_key_permutation_2, 48, 56);
	m[0] = uni_permut(buf, g_initial_permutation, 64, 64);
	l[0] = (m[0] >> 32);
	r[0] = (m[0] << 32) >> 32;
	i = 0;
	while (++i <= 16)
	{
		l[i] = r[i - 1];
		r[i] = l[i - 1] ^ f(r[i - 1], k[(fl->decrypt ? (17 - i) : i)]);
	}
	i = uni_permut(((r[16] << 32) | l[16]), g_final_permutation, 64, 64);
	return (i);
}
