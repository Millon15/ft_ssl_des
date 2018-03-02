
#include "../ft_ssl.h"

char			*des3_algorythm(char *line, ssize_t *l, t_fl *fl)
{
	char		*res[3];
	char		k[3][17];
	int			i;

	i = 0;
	while (i < 48)
	{
		ft_strncpy(k[(i / 16)], (fl->k + i), 16);
		k[(i / 16)][16] = '\0';
		i += 16;
	}
	// fl->des3 = 0;
	ft_strcpy(fl->k, k[0]);
	// res[0] = pre_endecrypt_des(line, *l, fl);
	ft_strcpy(fl->k, k[1]);
	fl->decrypt = 1;//fl->decrypt ? 0 : 1;
	// res[1] = pre_endecrypt_des(res[0], ft_strlen(res[0]), fl);
	ft_strcpy(fl->k, k[2]);
	fl->decrypt = 0;//fl->decrypt ? 1 : 0;
	// res[2] = pre_endecrypt_des(res[1], ft_strlen(res[0]), fl);
	// printf("%s\n%s\n\n", res[0], res[1]);
	free(res[0]);
	free(res[1]);
	*l = ft_strlen(res[2]);
	return (res[2]);
}
