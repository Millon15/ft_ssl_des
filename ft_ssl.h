/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:47:17 by vbrazas           #+#    #+#             */
/*   Updated: 2018/03/18 23:11:28 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# define BUFF_SIZE 4096
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef	struct		s_fl
{
	unsigned int	decrypt : 1;
	unsigned int	encrypt : 1;
	unsigned int	base64 : 1;
	unsigned int	des_ecb : 1;
	unsigned int	des_cbc : 1;
	unsigned int	des3 : 1;
	unsigned int	des3_ecb : 1;
	unsigned int	des3_cbc : 1;
	unsigned int	cbc_mode : 1;
	unsigned int	a : 1;
	int				bufs;
	unsigned long	iv;
	char			*in;
	char			*out;
	char			k[49];
	char			sub_k[3][17];
	char			iv_buf[17];
}					t_fl;

int					error(int ac, char **av, char *str, int i);
int					read_command(int ac, char **av, t_fl *fl, int i);
int					put_base64(char **av, t_fl *fl, ssize_t ret, ssize_t l);
char				*encrypt_base64(char *line, ssize_t ln, \
					size_t i, ssize_t j);
char				*decrypt_base64(char *line, ssize_t ln, \
					size_t i, ssize_t j);

int					put_des(char **av, t_fl *fl, ssize_t ret, ssize_t l);
unsigned long		endecrypt_des(unsigned long buf, t_fl *fl);
unsigned long		des3_algorythm(unsigned long buf, t_fl *fl);
char				*from_digit(unsigned long res);
void				make_subkey(t_fl *fl);

#endif
