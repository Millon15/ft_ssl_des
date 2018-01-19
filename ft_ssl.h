/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:47:17 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/19 21:33:24 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H
#include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "ft_printf/libft/libft.h"
# define BUFF_SIZE 64

typedef	struct		s_fl
{
	unsigned int	decrypt : 1;
	unsigned int	encrypt : 1;
	unsigned int	base64 : 1;
	int				bufsize;
	char			*in;
	char			*out;
}					t_fl;

int					ft_printf(const char *s, ...);

int					error(int ac, char **av, t_fl *fl, unsigned int i);
int					put_base64(char **av, t_fl *fl);

#endif