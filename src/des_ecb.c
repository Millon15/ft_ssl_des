/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:41:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/10 16:31:19 by vbrazas          ###   ########.fr       */
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
		tmp[0] = (c[i] << key_shift[i]) >> 28;
		tmp[1] = (d[i] << key_shift[i]) >> 28;
		c[i + 1] = tmp[0] | (c[i] << ((36 + key_shift[i])) >> 36);
		d[i + 1] = tmp[1] | (d[i] << ((36 + key_shift[i])) >> 36);
		// print_b(c[i + 1]);
		// printf("\n");
		// print_b(d[i + 1]);
		// printf("\n\n");
		i++;
	}
}

static	unsigned long	uni_permut(unsigned long k0, unsigned char perm[],\
int perm_len, int start_len)
{
	int					i;
	unsigned long		tmp;
	unsigned long		k1;

	i = 0;
	k1 = 0;
	while (i < perm_len)
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

	res[0] = uni_permut(text, expand_permutation, 48, 32);
	res[0] = (ki ^ res[0]) << 16;
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
		res[1] |= g_sboxes[a][b][c] << (4 * (-a + 7));
		// print_b(res[1]);
	}
	// print_b(res[1]);
	res[0] = uni_permut(res[1], g_pbox_permutation, 32, 32);
	// print_b(res[0]);
	return (res[0]);
}

char					*encrypt_des_ecb(unsigned long buf, t_fl *fl)
{
	unsigned long		i;
	unsigned long		m[17];
	unsigned long		k[17];
	unsigned long		l[17];
	unsigned long		r[17];

	// i = ft_atou_base(fl->k, 16);
	// i = to_digit(fl->k);
	k[0] = uni_permut(buf, key_permutation_1, 56, 64);
	// print_b(k[0]);
	// printf("%s\n\n", "00000000""11110000110011001010101011110101010101100110011110001111");
	l[0] = (k[0] >> 28);
	r[0] = (k[0] << 36) >> 36;
	shift_keys(l, r);
	i = 0;
	while (i++ < 16)
	{
		k[i] = uni_permut(((l[i] << 28) | r[i]), key_permutation_2, 48, 56);
		// print_b(k[i]);
		// printf("\n");
	}
	// printf("%s | %zu\n | %p\n", line, ft_strlen(line), line);
	m[0] = uni_permut(buf, initial_permutation, 64, 64);
	l[0] = (m[0] >> 32);
	r[0] = (m[0] << 32) >> 32;
	i = 0;
	while (++i <= 16)
	{
		l[i] = r[i - 1];
		r[i] = l[i - 1] ^ f(r[i - 1], k[i]);
		// print_b(r[i]);
	}
	// print_b(l[16]);
	// print_b(r[16]);
	i = uni_permut(((r[16] << 32) | l[16]), g_final_permutation, 64, 64);
	// print_b(i);
	// printf("%s\n\n", "1000010111101000000100110101010000001111000010101011010000000101");
	// return (ft_utoa_base(i, 16));
	return (from_digit(i));
}

int						put_des_ecb(char **av, t_fl *fl, ssize_t ret)
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
		r[1] = ft_strjoin(r[0], r[1]);
		free(r[2]);
	}
	r[2] = (fl->decrypt ? decrypt_des_ecb(r[1], fl) :\
		pre_encrypt_des_ecb(r[1], fl));
	fl->decrypt ? ft_putstr_fd(r[2], k[1]) : ft_putendl_fd(r[2], k[1]);
	free(r[2]);
	free(r[1]);
	free(r[0]);
	return (0);
}
