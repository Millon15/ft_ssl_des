/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:16:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/05 17:30:52 by vbrazas          ###   ########.fr       */
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
		res |= (s[i] || (i + passed) < l ? s[i++] : k);
		len++;
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
	ssize_t		l_buf;
	ssize_t		i;

	*l = (fl->a && fl->decrypt) ? ((*l - *l / 64) / 4 * 3) : *l;
	l_buf = *l;
	*l = (!(*l % 8) && !(fl->decrypt)) ? (*l + 8) : *l;
	buf[0] = endecrypt_des(to_digit((unsigned char *)line, l_buf, i), fl);
	i = 8;
	while ((*l - i) > 0)
	{
		buf[1] = endecrypt_des(to_digit((unsigned char *)line + i, l_buf, i), fl);
		buf[2] = buf[0];
		buf[0] = ft_strnjoin(buf[0], buf[1], (size_t)i, (size_t)8);
		free(buf[2]);
		free(buf[1]);
		i += 8;
	}
	*l = i;
	return (buf[0]);
}

static	int				help_put_des(char *r[], int k[], ssize_t l, t_fl *fl)
{
	if (ft_strlen(fl->k) != (fl->des3 ? 48 : 16))
		fix_num(fl->k, fl, (fl->des3 ? 48 : 16));
	if ((fl->des_cbc || fl->des3) && \
	(fl->iv_buf)[0] && ft_strlen(fl->iv_buf) != 16)
		fix_num(fl->iv_buf, fl, 16);
	if ((fl->des_cbc || fl->des3))
		fl->iv = ft_atou_base(fl->iv_buf, 16);
	free(r[0]);
	r[2] = ((fl->a && fl->decrypt) ? \
	(pre_endecrypt_des(((r[0] = decrypt_base64(r[1], l, \
	0, 0))), &l, fl)) : (pre_endecrypt_des(r[1], &l, fl)));
	free(r[1]);
	if (fl->decrypt && fl->a)
	{
		printf("r[0] = %s\n\n", r[0]);
		free(r[0]);
	}
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

int						put_des(char **av, t_fl *fl, ssize_t ret, ssize_t l)
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
		r[1] = ft_strnjoin(r[1], r[0], (size_t)l, (size_t)ret);
		free(r[2]);
		l += ret;
	}
	// write(1, r[1], l);
	// write(1, "\n123\n\n\n\n", 8);
	return (help_put_des(r, k, l, fl));
}
