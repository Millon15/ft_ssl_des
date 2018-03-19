/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:16:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/18 21:22:52 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

static	unsigned long	to_digit(unsigned char *s, ssize_t l, ssize_t passed)
{
	unsigned long	res;
	ssize_t			i;
	int				k;
	int				len;

	i = 0;
	k = 0;
	len = 0;
	res = 0;
	while (len != 8)
	{
		res <<= 8;
		if ((i + passed) >= l && !k)
			k = 8 - len;
		res |= (s[i] || ((i + passed) < l) ? s[i++] : k);
		len++;
	}
	return (res);
}

static	void			fix_num(char k[], int l)
{
	char	res[49];
	int		len;
	int		i;

	len = ft_strlen(k);
	if (len > l)
	{
		i = -1;
		while (++i < l)
			res[i] = k[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			res[i] = k[i];
		while (i < l)
			res[i++] = '0';
	}
	res[i] = '\0';
	ft_strncpy(k, res, (l + 1));
}

static	char			*pre_endecrypt_des(char *line, ssize_t *l, \
						ssize_t l_buf, t_fl *fl)
{
	unsigned long		f[3];
	char				*buf[3];
	ssize_t				i;

	*l = (fl->a && fl->decrypt) ? ((*l - *l / 64) / 4 * 3) : *l;
	l_buf = *l;
	*l = (!(*l % 8) && !(fl->decrypt)) ? (*l + 8) : *l;
	buf[0] = ft_memalloc(1);
	i = 0;
	while (i < *l)
	{
		f[0] = to_digit((unsigned char *)(line + i), l_buf, i);
		f[0] = (fl->cbc_mode && !(fl->decrypt)) ? (f[0] ^ fl->iv) : f[0];
		f[1] = fl->des3 ? des3_algorythm(f[0], fl) : endecrypt_des(f[0], fl);
		f[1] = (fl->cbc_mode && fl->decrypt) ? (f[1] ^ fl->iv) : f[1];
		fl->iv = (fl->cbc_mode && fl->decrypt) ? f[0] : f[1];
		buf[1] = from_digit(f[1]);
		buf[2] = buf[0];
		buf[0] = ft_strnjoin(buf[0], buf[1], i, 8);
		free(buf[2]);
		free(buf[1]);
		i += 8;
	}
	*l = i;
	return (buf[0]);
}

static	int				help_put_des(char *r[], int k[], ssize_t l, t_fl *fl)
{
	if (fl->cbc_mode && \
	(fl->iv_buf)[0] && ft_strlen(fl->iv_buf) != 16)
		fix_num(fl->iv_buf, 16);
	if (fl->cbc_mode)
		fl->iv = ft_atou_base(fl->iv_buf, 16);
	free(r[0]);
	if (fl->des3)
		make_subkey(fl);
	r[2] = ((fl->a && fl->decrypt) ? \
	(pre_endecrypt_des(((r[0] = decrypt_base64(r[1], l, \
	0, 0))), &l, 0, fl)) : (pre_endecrypt_des(r[1], &l, 0, fl)));
	free(r[1]);
	if (fl->decrypt && fl->a)
		free(r[0]);
	if (!(fl->decrypt) && fl->a)
		ft_putnendl_fd((r[1] = (encrypt_base64(r[2], \
		l, 0, 0))), k[1], ft_strlen(r[1]));
	else
		write(k[1], r[2], l - \
		((r[2][l - 1] >= 1 && r[2][l - 1] <= 8) ? r[2][l - 1] : 0));
	if ((!(fl->decrypt) && fl->a))
		free(r[1]);
	free(r[2]);
	return (0);
}

int						put_des(char **av, t_fl *fl, ssize_t ret, ssize_t l)
{
	char		*r[3];
	int			k[3];

	if ((k[0] = fl->in ? open(fl->in, O_RDONLY) : 0) == -1)
		return (error(-1, av, fl->in, 0));
	if ((k[1] = fl->out ? open(fl->out, O_WRONLY | \
	O_CREAT | O_TRUNC, 0666) : 1) == -1)
		return (error(-1, av, fl->out, 0));
	k[2] = (fl->bufs ? fl->bufs : BUFF_SIZE);
	r[0] = (char *)malloc(sizeof(char) * (k[2] + 1));
	r[1] = (char *)ft_memalloc(sizeof(char) * 1);
	while ((ret = read(k[0], r[0], k[2])))
	{
		r[0][ret] = '\0';
		r[2] = r[1];
		r[1] = ft_strnjoin(r[1], r[0], (size_t)l, (size_t)ret);
		free(r[2]);
		l += ret;
	}
	if (ft_strlen(fl->k) != (fl->des3 ? 48 : 16))
		fix_num(fl->k, (fl->des3 ? 48 : 16));
	return (help_put_des(r, k, l, fl));
}
