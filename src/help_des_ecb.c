/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_des_ecb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:41:02 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/10 17:49:25 by vbrazas          ###   ########.fr       */
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
	res = 0;
	l = 1;
	while (s[i] && (l % 8))
	{
		res <<= 8;
		res |= s[i++];
		l++;
	}
	if (!(s[i]))
	{
		l = 64;
		k = 0;
		while (!(res >> l))
		{
			l -= 8;
			k++;
		}
		while (k && !(res >> 56))
		{
			res <<= 8;
			res |= k;
		}
	}
	return (res);
}

char			*from_digit(unsigned long res)
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
	return (s);
}

char			*pre_encrypt_des_ecb(char *line, t_fl *fl)
{
	char		*line2;
	char		*line2_buf;
	char		*buf;
	size_t		l;
	size_t		i;

	l = ft_strlen(line);
	line2 = (char *)malloc(sizeof(char) * (l + 1));
	line2[l] = '\0';
	line2 = encrypt_des_ecb(to_digit(line), fl);
	i = 8;
	// printf("l = %zu\n", l);
	while ((l - i) > 8)
	{
		buf = encrypt_des_ecb(to_digit(line + i), fl);
		// printf("AAA : %zu | %zu | ", l - i, i);
		// printf("%s\n", buf);
		line2_buf = line2;
		line2 = ft_strjoin(line2, buf);
		free(line2_buf);
		i += 8;
	}
	return (line2);
}
