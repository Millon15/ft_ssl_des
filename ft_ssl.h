/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:47:17 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/03 19:08:11 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H
# define BUFF_SIZE 4096
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "ft_printf/libft/libft.h"

#include <stdio.h>


void	print_b(unsigned long a)
{
	int					i;

	i = 0;
	while (i < 64)
		printf("%lu", (a << i++) >> 63);
}


typedef	struct		s_fl
{
	unsigned int	decrypt : 1;
	unsigned int	encrypt : 1;
	unsigned int	base64 : 1;
	unsigned int	des_ecb : 1;
	unsigned int	bufs : 1;
	unsigned int	a : 1;
	char			*in;
	char			*out;
	char			*k;
}					t_fl;

int					ft_printf(const char *s, ...);

int					error(int ac, char **av, char *str, int i);
int					read_args(int ac, char **av, t_fl *fl, int i);
int					put_base64(char **av, t_fl *fl, ssize_t ret);
int					put_des_ecb(char **av, t_fl *fl, ssize_t ret);

#endif