/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:41:13 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/01 21:44:29 by vbrazas          ###   ########.fr       */
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
	unsigned long		k1;

	i = -1;
	k1 = 0;
	while (++i < 64)
	{
		// printf("%lu", k1 = (k1 | (((k0 << pc_1[i]) >> 63) << (63 - i))));
		printf("%lu", ((k0 << i) >> 63));
	}
	// k1 >>= 8;
	return (k1);
}

static	char			*encrypt_des_ecb(char *line, t_fl *fl)
{
	unsigned long		k0;
	unsigned long		k1;

	k0 = ft_atou_base(fl->k, 16);
	k1 = permut_pc_1(k0);
	// printf("%lu\n", k1);
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
