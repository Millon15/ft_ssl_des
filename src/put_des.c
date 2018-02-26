/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:16:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/25 20:30:25 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	unsigned long	to_digit(unsigned char *s)
{
	unsigned long	res;
	int				i;
	int				l;
	int				k;

	i = 0;
	k = 0;
	l = 0;
	res = 0;
	while (l != 8)
	{
		res <<= 8;
		if (!s[i] && !k)
			k = 8 - l;
		res |= (s[i] ? s[i++] : k);
		l++;
	}
	return (res);
}

static	void			fix_num(t_fl *fl)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(fl->k);
	if (len > 16)
		res = ft_strsub(fl->k, 0, 16);
	else
	{
		i = -1;
		res = (char *)malloc(sizeof(char) * 17);
		while (++i < len)
			res[i] = (fl->k)[i];
		while (i < 16)
			res[i++] = '0';
		res[i] = '\0';
	}
	fl->k = res;
}

static	char			*pre_endecrypt_des_ecb(char *line, ssize_t l, t_fl *fl)
{
	char		*line2;
	char		*line2_buf;
	char		*buf;
	int			i;

	if (ft_strlen(fl->k) != 16)
		fix_num(fl);
	l = !(l % 8) ? (l + 8) : l;
	line2 = endecrypt_des(to_digit((unsigned char *)line), fl->k, fl->decrypt);
	i = 8;
	while ((l - i) > 0)
	{
		buf = endecrypt_des(to_digit((unsigned char *)line + i), fl->k, fl->decrypt);
		line2_buf = line2;
		line2 = ft_strjoin(line2, buf);
		free(line2_buf);
		free(buf);
		i += 8;
	}
	return (line2);
}

static	int				help_put_des_ecb(char *r[], int k[], ssize_t l, t_fl *fl)
{
	if (fl->decrypt)
		r[2] = fl->a ? (pre_endecrypt_des_ecb((decrypt_base64(r[1], ft_strlen(\
		r[1]), 0, 0)), l, fl)) : (pre_endecrypt_des_ecb(r[1], l, fl));
	else
		r[2] = pre_endecrypt_des_ecb(r[1], l, fl);
	free(r[1]);
	if (fl->decrypt)
		fl->a ? write(k[1], r[2], l / 3 * 4) : write(k[1], r[2], l);
	else
		fl->a ? ft_putendl_fd((r[1] = (encrypt_base64(r[2], ft_strlen(r[2])\
		, 0, 0))), k[1]) : ft_putstr_fd(r[2], k[1]);
	if ((!(fl->decrypt) && fl->a))
		free(r[1]);
	free(r[0]);
	free(r[2]);
	return (0);
}

int						put_des_ecb(char **av, t_fl *fl, ssize_t ret)
{
	char		*r[3];
	int			k[3];
	ssize_t		l;

	if ((k[0] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1)
		return (error(-1, av, fl->in, 0));
	if ((k[1] = fl->out ? open(fl->out, O_WRONLY) : 1) == -1)
		return (error(-1, av, fl->out, 0));
	k[2] = (fl->bufs ? fl->bufs : BUFF_SIZE);
	r[0] = (char *)malloc(sizeof(char) * (k[2] + 1));
	r[1] = (char *)ft_memalloc(sizeof(char) * 1);
	r[1][0] = '\0';
	l = 0;
	while ((ret = read(k[0], r[0], k[2])))
	{
		r[0][ret] = '\0';
		r[2] = r[1];
		r[1] = ft_strjoin(r[1], r[0]);
		free(r[2]);
		l += ret;
	}
	return (help_put_des_ecb(r, k, l, fl));
}
