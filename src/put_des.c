/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:16:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/04 22:03:59 by vbrazas          ###   ########.fr       */
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

static	void			fix_num(char k[], t_fl *fl, int l)
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

static	char			*pre_endecrypt_des(char *line, ssize_t *l, t_fl *fl)
{
	char		*buf[3];
	int			i;

	if (ft_strlen(fl->k) != (fl->des3 ? 48 : 16))
		fix_num(fl->k, fl, (fl->des3 ? 48 : 16));
	if ((fl->des_cbc || fl->des3) && ft_strlen(fl->iv_buf) != 16)
		fix_num(fl->iv_buf, fl, 16);
	fl->iv = ft_atou_base(fl->iv_buf, 16);
	*l = (!(*l % 8) && !(fl->decrypt)) ? (*l + 8) : *l;
	// if (fl->des3)
	// 	return (des3_algorythm(line, &l, fl));
	buf[0] = endecrypt_des(to_digit((unsigned char *)line), fl);
	i = 8;
	while ((*l - i) > 0)
	{
		buf[1] = endecrypt_des(to_digit((unsigned char *)line + i), fl);
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
	ssize_t		x;

	free(r[0]);
	r[2] = ((fl->a && fl->decrypt) ? \
	(pre_endecrypt_des(((r[0] = decrypt_base64(r[1], ft_strlen(\
	r[1]), 0, 0))), &l, fl)) : (pre_endecrypt_des(r[1], &l, fl)));
	free(r[1]);
	if (fl->decrypt && fl->a)
		free(r[0]);
	if (!(fl->decrypt) && fl->a)
		ft_putnendl_fd((r[1] = (encrypt_base64(r[2], \
		l, 0, 0))), k[1], ft_strlen(r[1]));
	else
		write(k[1], r[2], l);
	if ((!(fl->decrypt) && fl->a))
		free(r[1]);
	free(r[2]);
	return (0);
}

int						put_des(char **av, t_fl *fl, ssize_t ret)
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
	return (help_put_des(r, k, l, fl));
}
