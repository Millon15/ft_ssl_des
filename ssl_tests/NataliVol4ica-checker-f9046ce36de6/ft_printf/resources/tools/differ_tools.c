
#include "tools.h"
#include <stdlib.h>
#include <errno.h>

void	set_num(char *num, int n)
{
	for (int i = 0; i < 3; i++)
		num[i] = '0';
	num[2] += n % 10;
	n /= 10;
	num[1] += n % 10;
	n /= 10;
	num[0] += n;
}

char	*get_test_name(int n, int ismain)
{
	char	*ans;
	char	*type;
	char	*num;
	char	*temp;

	num = ft_strnew(3);
	type = ft_strnew(1);
	set_num(num, n);
	type[0] = ismain ? 'm' : 'b';
	temp = ft_strjoin("../testing_results/test_", type);
	free(type);
	ans = ft_strjoin(temp, num);
	free(num);
	free(temp);
	temp = ans;
	ans = ft_strjoin(temp, "_");
	free(temp);
	return (ans);
}

char	*get_code_name(int n, int ismain)
{
	char	*ans;
	char	*type;
	char	*num;
	char	*temp;

	num = ft_strnew(3);
	type = ft_strnew(1);
	set_num(num, n);
	type[0] = ismain ? 'm' : 'b';
	temp = ft_strjoin("../generated_testers/test_", type);
	free(type);
	ans = ft_strjoin(temp, num);
	free(num);
	free(temp);
	temp = ans;
	ans = ft_strjoin(temp, ".c");
	free(temp);
	return (ans);
}

t_read_lines	*new_differ_test(char *name, char *code_file)
{
	t_read_lines	*r;
	char		*fname;

	if (!(r = (t_read_lines*)malloc(sizeof(t_read_lines)))) bad_malloc();
	fname = ft_strjoin(name, P_PRINT);
	r->printf_line = new_readline(fname, "r");
	free(fname);
	fname = ft_strjoin(name, P_RET);
	r->printf_ret = new_readline(fname, "r");
	free(fname);
	fname = ft_strjoin(name, F_PRINT);
	r->ft_printf_line = new_readline(fname, "r");
	free(fname);
	fname = ft_strjoin(name, F_RET);
	r->ft_printf_ret = new_readline(fname, "r");
	free(fname);
	r->source_code = new_readline(code_file, "r");
	free(name);
	free(code_file);
	return (r);
}

void		close_differ_test(t_read_lines *r)
{
	close_readline(r->printf_line);
	close_readline(r->printf_ret);
	close_readline(r->ft_printf_line);
	close_readline(r->ft_printf_ret);
	close_readline(r->source_code);
	free(r);
}

// ============= RESULT FUNCS =============== \\

void			zero_result(void)
{
	for (enum lens l = lnone; l <= lt; l++)
	{
		for (enum m_types t = td; t <= tperc; t++)
		{
			result.main_values[t][l].num_of_tests = 0;
			result.main_values[t][l].num_of_fails = 0;
		}
		for (enum b_types t = te; t <= tn; t++)
		{
			result.bonus_values[t][l].num_of_tests = 0;
			result.bonus_values[t][l].num_of_fails = 0;
		}
	}
	result.apostrophe.num_of_tests = 0;
	result.apostrophe.num_of_fails = 0;
	result.stars.num_of_tests = 0;
	result.stars.num_of_fails = 0;
	result.dollar.num_of_tests = 0;
	result.dollar.num_of_fails = 0;
}

//============ RESULT PRINTING =============\\

void			choose_color(t_result_info t)
{
	int	percent;

	if (t.num_of_tests == 0)
	{
		printf("\033[0;37m""none""\033[0m");
		return ;
	}
	if (t.num_of_fails == 0)
	{
		printf("\x1b[32m""100%%""\x1b[0m");
		return ;
	}
	percent = (int)(100 - 100 * t.num_of_fails / t.num_of_tests);
	percent = percent == 100 ? 99 : percent;
	printf("\x1b[31m""%3.2d%%""\x1b[0m", percent);
}

void			print_m_res(enum m_types t, int is_bonus)
{
	size_t	fails = 0;
	int		max;

	printf("   %%");
	if (t == td) printf("d"); else
	if (t == tD) printf("D"); else
	if (t == ti) printf("i"); else
	if (t == to) printf("o"); else
	if (t == tO) printf("O"); else
	if (t == tu) printf("u"); else
	if (t == tU) printf("U"); else
	if (t == tx) printf("x"); else
	if (t == tX) printf("X"); else
	if (t == tc) printf("c"); else
	if (t == tC) printf("C"); else
	if (t == ts) printf("s"); else
	if (t == tS) printf("S"); else
	if (t == tp) printf("p");
	printf(" : [");
	max = is_bonus ? lt : lz;
	for (enum lens l = lnone; l <= max; l++)
	{
		choose_color(result.main_values[t][l]);
		fails += result.main_values[t][l].num_of_fails;
		if (l != max) printf("|");
	}
	printf("]");
	if (fails)
		printf("\x1b[31m"" Fails : %zu""\x1b[0m", fails);
	printf("\n");
}

void			print_b_res(enum b_types t)
{
	size_t fails = 0;

	printf("   %%");
	if (t == te) printf("e"); else
	if (t == tE) printf("E"); else
	if (t == tf) printf("f"); else
	if (t == tF) printf("F"); else
	if (t == ta) printf("a"); else
	if (t == tA) printf("A"); else
	if (t == tg) printf("g"); else
	if (t == tG) printf("G"); else
	if (t == tn) printf("n");
	printf(" : [");
	for (enum lens l = lnone; l <= lt; l++)
	{
		choose_color(result.bonus_values[t][l]);
		fails += result.bonus_values[t][l].num_of_fails;
		if (l != lt) printf("|");
	}
	printf("]");
	if (fails)
		printf("\x1b[31m"" Fails : %zu""\x1b[0m", fails);
	printf("\n");
}

void			print_result(int is_bonus)
{
	if (is_bonus == 0)
	{
	printf("        [ -  | hh | h  | l  | ll | j  | z  ]\n");
	for (enum m_types t = td; t < tperc; t++)
		print_m_res(t, is_bonus);
	if (!is_bonus)
		return ;
	}
	printf("        [ -  | hh | h  | l  | ll | j  | z  | L  | t  ]\n");
	for (enum m_types t = td; t < tperc; t++)
		print_m_res(t, is_bonus);
	printf("\n");
	for (enum b_types t = te; t <= tn; t++)
		print_b_res(t);
	printf("\n   \'      : [");
	choose_color(result.apostrophe);
	printf("]\n   *.*    : [");
	choose_color(result.stars);
	printf("]\n   $, *.$ : [");
	choose_color(result.dollar);
	printf("]\n|============================|\n");
}
