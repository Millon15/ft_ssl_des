/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:41:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/03 21:30:09 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"
#include "permutations.h"

static	char			*decrypt_des_ecb(char *line, t_fl *fl)
{
	return (NULL);
}

static	unsigned long	permut_pc_1(unsigned long k0)
{
	int					i;
	unsigned long		tmp;
	unsigned long		k1;

	i = 0;
	k1 = 0;
	while (i < 56)
	{
		tmp = ((k0 >> (64 - pc_1[i++])) << 63) >> 63;
		k1 <<= 1;
		k1 += tmp;
	}
	return (k1);
}

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

static	unsigned long	permut_pc_2(unsigned long k0, unsigned char perm[], int perm_len, int start_len)
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

static	char			*encrypt_des_ecb(char *line, t_fl *fl)
{
	unsigned long		key;
	unsigned long		k[17];
	unsigned long		c[17];
	unsigned long		d[17];

	key = ft_atou_base(fl->k, 16);
	k[0] = permut_pc_2(key, pc_1, 56, 64);
	// print_b(k[0]);
	// printf("\n%s\n\n", "00000000""11110000110011001010101011110101010101100110011110001111");
	c[0] = (k[0] >> 28);
	d[0] = (k[0] << 36) >> 36;
	shift_keys(c, d);
	key = 0;
	while (key++ < 16)
	{
		k[key] = permut_pc_2(((c[key] << 28) | d[key]), pc_2, 48, 56);
		// print_b(k[key]);
		// printf("\n");
	}
	return (NULL);
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
		r[1] = ft_strjoin(r[1], r[0]);
		free(r[2]);
	}
	r[1] = (fl->decrypt ? decrypt_des_ecb(r[1], fl) :\
		encrypt_des_ecb(r[1], fl));
	fl->decrypt ? ft_putstr_fd(r[1], k[1]) : ft_putendl_fd(r[1], k[1]);
	free(r[1]);
	free(r[0]);
	return (0);
}
