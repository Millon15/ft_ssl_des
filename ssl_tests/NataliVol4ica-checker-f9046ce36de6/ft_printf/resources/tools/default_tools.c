
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*ans;
	int		strl;
	int		i;

	strl = ft_strlen(str);
	if (!str)
		return (NULL);
	if (!(ans = (char*)malloc(sizeof(char) * (strl + 1))))
		bad_malloc();
	i = -1;
	while (++i < strl)
		ans[i] = str[i];
	ans[strl] = '\0';
	return (ans);
}

static size_t	count_num_of_words(char const *s, char c)
{
	size_t	ans;
	size_t	i;

	i = 0;
	ans = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ans++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (ans);
}

static char	*get_next_word(char const *s, int *pos, char c)
{
	int		i;
	char	*ans;

	i = 0;
	while (s[*pos + i] && s[*pos + i] != c)
		i++;
	ans = ft_strnew(i);
	if (!ans)
		return (NULL);
	i = 0;
	while (s[*pos + i] && s[*pos + i] != c)
	{
		ans[i] = s[*pos + i];
		i++;
	}
	ans[i] = '\0';
	*pos = *pos + i;
	return (ans);
}

static void	second_part(char const *s, char **ans, int nofw, char c)
{
	int		nw;
	int		i;

	i = 0;
	nw = 0;
	while (nw != nofw)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			ans[nw] = get_next_word(s, &i, c);
			if (!ans[nw])
			{
				while (--nw >= 0)
					free(ans[nw]);
				*ans = NULL;
				return ;
			}
			nw++;
		}
	}
}

char		**ft_strsplit(char const *s, size_t *n, char c)
{
	char	**ans;
	size_t	num_of_words;

	if (!s)
		return (NULL);
	num_of_words = count_num_of_words(s, c);
	ans = (char**)malloc(sizeof(char*) * (num_of_words + 1));
	if (!ans)
		return (NULL);
	second_part(s, ans, num_of_words, c);
	ans[num_of_words] = NULL;
	*n = num_of_words;
	return (ans);
}

char	*ft_strnew(int n)
{
	char	*ans;

	if (!(ans = (char*)malloc(sizeof(char) * (n + 1)))) bad_malloc();
	for (size_t	i = 0; i <= n; i++)
		ans[i] = '\0';
	return (ans);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	res = ft_strnew(ft_strlen((char*)s1) + ft_strlen((char*)s2));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	if (s1)
		while (s1[++i])
			res[i] = s1[i];
	if (s2)
		while (s2[++j])
			res[i + j] = s2[j];
	return (res);
}

