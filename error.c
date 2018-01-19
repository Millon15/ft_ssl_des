/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:09:45 by vbrazas           #+#    #+#             */
/*   Updated: 2018/01/19 20:11:22 by vbrazas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		error(int ac, char **av, t_fl *fl, unsigned int i)
{
	if (ac == 1)
		ft_putendl("usage: ft_ssl command [command opts] [command args]");
	else if (ac >= 2)
	{
		ft_putstr("ft_ssl: Error: '");
		ft_putstr(av[1]);
		ft_putstr("' is an invalid command.\nStandard commands:\n\n\
Message Digest commands:\n\nCipher commands:\nbase64\n");
//des\ndes-ecb\ndes-cbc\n");
	}
	else if (ac == -1)
	{
		ft_putstr("unknown option '");
		ft_putstr(av[i]);
		ft_putstr("options are\n-in <file>\tinput file\n\
-out <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n\
Cipher Types\ndes\t\tdes-ecb\t\tdes-cbc\n");
	}
	else if (ac == -2)
		ft_putstr("options are\n-in <file>\tinput file\n\
-out <file>\toutput file\n-e\t\tencrypt\n-d\t\tdecrypt\n\
Cipher Types\ndes\t\tdes-ecb\t\tdes-cbc\n");
	free(fl);
	return (-1);
}
