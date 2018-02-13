/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_des_ecb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:41:02 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/13 18:40:01 by vbrazas          ###   ########.fr       */
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
	while ((l % 8))
	{
		res <<= 8;
		res |= s[i] ? s[i++] : 0;
		l++;
	}
	// if (!(s[i]))
	// {
	// 	l = 64;
	// 	k = 0;
	// 	while (!(res >> l))
	// 	{
	// 		l -= 8;
	// 		k++;
	// 	}
	// 	while (k && !(res >> 56))
	// 	{
	// 		res <<= 8;
	// 		res |= k;
	// 	}
	// }
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
	int			l;
	int			i;

	l = ft_strlen(line);
	line2 = (char *)malloc(sizeof(char) * (l + 1));
	line2[l] = '\0';
	line2 = encrypt_des_ecb(to_digit(line), fl);
	i = 8;
	// printf("l = %i\n", l);
	while ((l - i) > 0)
	{
		buf = encrypt_des_ecb(to_digit(line + i), fl);
		// printf("AAA : %zu | %zu | ", l - i, i);
		// printf("%s\n", buf);
		line2_buf = line2;
		line2 = ft_strjoin(line2, buf);
		free(line2_buf);
		free(buf);
		i += 8;
	}
	// printf("%zu | %zu | %zu\n", l - i, l, i);
	// if (!(l - i))
	// 	return (line2);
	// buf = (char *)ft_memalloc(sizeof(char) * 9);
	// i = l - i;
	// ft_memcpy(buf, line + i, i);
	// while (i < 8)
	// 	buf[i++] = '0';
	// printf("AAA : %i | %s\n", buf[0], buf);
	// line2_buf = buf;
	// buf = encrypt_des_ecb(to_digit(buf), fl);
	// free(line2_buf);
	// line2_buf = line2;
	// line2 = ft_strjoin(line2, buf);
	// free(line2_buf);
	// free(buf);
	return (line2);
}
