/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:47:17 by vbrazas           #+#    #+#             */
/*   Updated: 2018/02/21 19:31:09 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H
# define BUFF_SIZE 4096
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "libft/libft.h"

#include <stdio.h>

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

int					error(int ac, char **av, char *str, int i);
int					read_args(int ac, char **av, t_fl *fl, int i);
int					put_base64(char **av, t_fl *fl, ssize_t ret);
int					put_des_ecb(char **av, t_fl *fl, ssize_t ret);
char				*encrypt_des_ecb(unsigned long buf, t_fl *fl);
char				*decrypt_des_ecb(char *line, t_fl *fl);
void				print_b(unsigned long a);


#endif