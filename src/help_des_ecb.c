/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_des_ecb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:41:02 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/21 18:53:01 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ssl.h"

char			*decrypt_des_ecb(char *line, t_fl *fl)
{
	return (NULL);
}

void			print_b(unsigned long a)
{
	int			i;

	i = 0;
	while (i < 64)
		printf("%lu", (a << i++) >> 63);
	printf("\n");
}

unsigned long	to_digit(char *s)
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
	// printf("%s ", ft_utoa_base(res, 16));
	return (res);
}

char			*from_digit(unsigned long res)
{
	char	*s;
	int		a;
	int		i;

	// printf("%s ", ft_utoa_base(res, 16));
	s = (char *)malloc(sizeof(char) * 9);
	i = 0;
	a = 0;
	while (a != 64)
	{
		s[i++] = (res << a) >> 56;
		a += 8;
	}
	return (s);
}

char			*pre_encrypt_des_ecb(char *line, t_fl *fl)
{
	char		*line2;
	char		*line2_buf;
	char		*buf;
	int			l;
	int			i;

	l = ft_strlen(line);
	l = !(l % 8) ? (l + 8) : l;
	line2 = (char *)malloc(sizeof(char) * (l + 1));
	line2[l] = '\0';
	line2 = encrypt_des_ecb(to_digit(line), fl);
	i = 8;
	while ((l - i) > 0)
	{
		buf = encrypt_des_ecb(to_digit(line + i), fl);
		line2_buf = line2;
		line2 = ft_strjoin(line2, buf);
		free(line2_buf);
		free(buf);
		i += 8;
	}
	// printf("\n\n");
	return (line2);
}
