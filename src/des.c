/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:41:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/27 14:44:10 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "permutations.h"

static	char			*from_digit(unsigned long res)
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
		// print_b(c[i + 1]);
		// printf("\n");
		// print_b(d[i + 1]);
		// printf("\n\n");
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
	// print_b(res[0]);
	// printf("\n%s\n\n", "011000010001011110111010100001100110010100100111");
	a = -1;
	res[1] = 0;
	while (++a < 8)
	{
		l[a] = ((res[0] << (6 * a)) >> (6 * 7)) >> 16;
		b = ((l[a] << 63) >> 63) | (((l[a] >> 5) << 63) >> 62);
		c = ((l[a] >> 1) << 60) >> 60;
		// print_b(l[a]);
		// print_b(b);
		// print_b(c);
		// printf("\n\n");
		res[1] |= (g_sboxes[a][b][c] << (4 * (7 - a)));
		// print_b(res[1]);
	}
	// print_b(res[1]);
	res[0] = uni_permut(res[1], g_pbox_permutation, 32, 32);
	// print_b(res[0]);
	return (res[0]);
}

char					*endecrypt_des(unsigned long buf, t_fl *fl)
{
	unsigned long		i;
	unsigned long		m[17];
	unsigned long		k[17];
	unsigned long		l[17];
	unsigned long		r[17];

	// printf("key = %lu\n", ft_atou_base(key, 16));
	// print_b(ft_atou_base(key, 16));
	// printf("%s\n\n", "0001001100110100010101110111100110011011101111001101111111110001");
	k[0] = uni_permut(ft_atou_base(fl->k, 16), g_key_permutation_1, 56, 64);
	// print_b(k[0]);
	// printf("%s\n\n", "00000000""11110000110011001010101011110101010101100110011110001111");
	l[0] = (k[0] >> 28);
	r[0] = (k[0] << 36) >> 36;
	shift_keys(l, r);
	i = 0;
	while (i++ < 16)
	{
		k[i] = uni_permut(((l[i] << 28) | r[i]), g_key_permutation_2, 48, 56);
		// print_b(k[i]);
	}
	// printf("%s | %zu\n | %p\n", line, ft_strlen(line), line);
	buf = (fl->des_cbc && !(fl->decrypt)) ? (buf ^ fl->iv) : buf;
	m[0] = uni_permut(buf, g_initial_permutation, 64, 64);
	l[0] = (m[0] >> 32);
	r[0] = (m[0] << 32) >> 32;
	i = 0;
	while (++i <= 16)
	{
		l[i] = r[i - 1];
		r[i] = l[i - 1] ^ f(r[i - 1], k[(fl->decrypt ? (17 - i) : i)]);
		// print_b(r[i]);
	}
	// print_b(l[16]);
	// print_b(r[16]);
	i = uni_permut(((r[16] << 32) | l[16]), g_final_permutation, 64, 64);
	i = (fl->des_cbc && fl->decrypt) ? (i ^ fl->iv) : i;
	fl->iv = (fl->des_cbc && !(fl->decrypt)) ? i : buf;
	// print_b(i);
	// printf("%s\n\n", "1000010111101000000100110101010000001111000010101011010000000101");
	// return (ft_utoa_base(i, 16));
	return (from_digit(i));
}
