/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:16:04 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/28 22:40:14 by vbrazas          ###   ########.fr       */
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

static	char			*pre_endecrypt_des(char *line, ssize_t l, t_fl *fl);

static	char			*des3_algorythm(char *line, ssize_t l, t_fl *fl)
{
	char		*line3;
	char		**res;
	char		k[3][17];
	int			i;

	i = 0;
	while (i < 48)
	{
		ft_strncpy(k[(i / 16)], (fl->k + i), 16);
		k[(i / 16)][16] = '\0';
		i += 16;
	}
	fl->des3 = 0;
	// fl->des_cbc = 1;
	res = (char **)malloc(sizeof(char *) * 3);
	ft_strcpy(fl->k, k[0]);
	res[0] = pre_endecrypt_des(line, l, fl);
	ft_strcpy(fl->k, k[1]);
	fl->decrypt = fl->decrypt ? 0 : 1;
	res[1] = pre_endecrypt_des(res[0], ft_strlen(res[0]), fl);
	ft_strcpy(fl->k, k[2]);
	res[2] = pre_endecrypt_des(res[1], ft_strlen(res[0]), fl);
	printf("%s\n%s\n%s\n", res[0], res[1], res[2]);
	line3 = (char *)ft_memalloc(sizeof(char) * 20);
	ft_strcpy(line3, "des3 is testing\n");
	return (line3);
}

static	char			*pre_endecrypt_des(char *line, ssize_t l, t_fl *fl)
{
	char		*line2;
	char		*line2_buf;
	char		*buf;
	int			i;

	if (ft_strlen(fl->k) != (fl->des3 ? 48 : 16))
		fix_num(fl->k, fl, (fl->des3 ? 48 : 16));
	if ((fl->des_cbc || fl->des3) && ft_strlen(fl->iv_buf) != 16)
		fix_num(fl->iv_buf, fl, 16);
	fl->iv = ft_atou_base(fl->iv_buf, 16);
	l = !(l % 8) ? (l + 8) : l;
	if (fl->des3)
		return (des3_algorythm(line, l, fl));
	line2 = endecrypt_des(to_digit((unsigned char *)line), fl);
	i = 8;
	while ((l - i) > 0)
	{
		buf = endecrypt_des(to_digit((unsigned char *)line + i), fl);
		line2_buf = line2;
		line2 = ft_strjoin(line2, buf);
		free(line2_buf);
		free(buf);
		i += 8;
	}
	return (line2);
}

static	int				help_put_des(char *r[], int k[], ssize_t l, t_fl *fl)
{
	free(r[0]);
	if (fl->decrypt)
		r[2] = (fl->a ? (pre_endecrypt_des(((r[0] = decrypt_base64(r[1], ft_strlen(\
		r[1]), 0, 0))), l, fl)) : (pre_endecrypt_des(r[1], l, fl)));
	else
		r[2] = pre_endecrypt_des(r[1], l, fl);
	free(r[1]);
	if (fl->decrypt && fl->a)
		free(r[0]);
	if (fl->decrypt)
		fl->a ? write(k[1], r[2], l / 3 * 4) : write(k[1], r[2], l);
	else
		fl->a ? ft_putendl_fd((r[1] = (encrypt_base64(r[2], ft_strlen(r[2])\
		, 0, 0))), k[1]) : ft_putstr_fd(r[2], k[1]);
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
