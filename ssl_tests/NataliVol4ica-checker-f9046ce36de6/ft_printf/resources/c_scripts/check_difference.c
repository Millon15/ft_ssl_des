/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 16:05:44 by nkolosov          #+#    #+#             */
/*   Updated: 2017/12/15 16:05:44 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libc.h>
#include <stdlib.h>
#include "tools.h"

#define MAINTYPES "dDioOuUxXcCsSp%" //15
#define BONUSTYPES "eEfFaAgGn" //9

char	*extra;

void	save_test(char *str, int is_fail)
{
	size_t	i;
	size_t	len;

	if (strstr(str, "%n"))
	{
		result.bonus_values[tn][0].num_of_tests++;
		result.bonus_values[tn][0].num_of_fails += is_fail;
		return ;
	}
	while (str[0] && str[0] != '|')
		str++;
	str++;
	i = 1;
	while (str[0] && str[i] != '|')
		i++;
	if (!str[0])
	{
		printf("No '|' in file. Totally incorrect test. Quitting the differer. Check the fails file.\n");
		exit (0);
	}
	str[i] = '\0';
	i -= 2;
	if (str[i] == 'h' && str[i - 1] == 'h' ) len = lhh; else
	if (str[i] == 'h') len = lh; else
	if (str[i] == 'l' && str[i - 1] == 'l' ) len = lll; else
	if (str[i] == 'l') len = ll; else
	if (str[i] == 'j') len = lj; else
	if (str[i] == 'z') len = lz; else
	if (str[i] == 'L') len = lL; else
	if (str[i] == 't') len = lt; else
	len = lnone;
	i++;
	if (strchr(str, '\''))
	{
		result.apostrophe.num_of_tests++;
		result.apostrophe.num_of_fails += is_fail;
	}
	for (size_t typ = 0; typ < tmmax; typ++)
		if (str[i] == MAINTYPES[typ])
		{
			result.main_values[typ][len].num_of_fails += is_fail;
			result.main_values[typ][len].num_of_tests++;
			if (strchr(str, '*'))
			{
				if (strchr(str, '$'))
				{
					result.dollar.num_of_tests++;
					result.dollar.num_of_fails += is_fail;
				}
				else
				{
					result.stars.num_of_tests++;
					result.stars.num_of_fails += is_fail;
				}
			}
			else if (strchr(str, '$'))
			{
				result.dollar.num_of_tests++;
				result.dollar.num_of_fails += is_fail;
			}
			return ;
		}
	for (size_t typ = 0; typ < tbmax; typ++)
		if (str[i] == BONUSTYPES[typ])
		{
			result.bonus_values[typ][len].num_of_fails += is_fail;
			result.bonus_values[typ][len].num_of_tests++;
			return ;
		}
}

void	print_fail(FILE *fails, t_read_lines *r)
{
	char	*temp;

	fprintf(fails, "=============\\\n");
	r->printf_line->str[5] = '\0';
	r->source_code->filename[6] = '\0';
	if ((temp = strstr(&r->source_code->str[11], "ft_")))
	{
		temp[0] = ' ';
		temp[1] = ' ';
		temp[2] = ' ';
	}
	fprintf(fails, "Fail %s[%s]: %s\n", &r->source_code->filename[21], r->printf_line->str, &r->source_code->str[11]);
	r->printf_line->str[5] = '|';
	r->source_code->filename[8] = '.';
	fprintf(fails, "Your str : \"%s\"\n", &r->ft_printf_line->str[5]);
	fprintf(fails, "Corr str : \"%s\"\n", &r->printf_line->str[5]);
	fprintf(fails, "Your ret : \"%s\"\n", r->ft_printf_ret->str);
	fprintf(fails, "Corr ret : \"%s\"\n", r->printf_ret->str);
	if (extra) fprintf(fails, "Extra code: %s", extra);
}

void	check_file(t_read_lines *r, FILE *fails)
{
	size_t	curtest = 0;
	size_t	curcode = 0;
	size_t	i = 0;

	read_delim(r->source_code, '@');
	extra = strstr(r->source_code->str, "setvbuf(ft_printf_ret, NULL, _IONBF, 0);");
	extra = strchr(extra, '\n');
	extra++;
	extra[strlen(extra) - 2] = '\0';
	while (extra[0] == '\n' || extra[0] == '\t' || extra[0] == ' ') extra++;
	if (extra[0] == '\0') extra = NULL; else extra = ft_strdup(extra);
	while (read_line(r->printf_line))
	{
		total.num_of_tests++;
		read_line(r->ft_printf_line);
		if (r->printf_line->len == 1)
			continue ;
		read_line(r->printf_ret);
		read_line(r->ft_printf_ret);
		skip_read_line(r->source_code, 5);
		if ((strcmp(r->printf_line->str, r->ft_printf_line->str) != 0 ||
			strcmp(r->printf_ret->str, r->ft_printf_ret->str) != 0) &&
			!(strcmp(r->printf_ret->str, "-1") == 0))
		{
			print_fail(fails, r);
			save_test(r->source_code->str, 1);
			total.num_of_fails++;
		}
		else
			save_test(r->source_code->str, 0);
		read_delim(r->source_code, '@');
		curtest++;
	}
	free(extra);
}

int		main(int ac, char **av)
{
	size_t			num_of_main_tests;
	size_t			num_of_bonus_tests;
	t_read_lines	*r;
	FILE			*fails;

	if (ac != 3)
		return (1);
	fflush(stdout);
	total.num_of_tests = 0;
	total.num_of_fails = 0;
	num_of_main_tests = atoi(av[1]);
	num_of_bonus_tests = atoi(av[2]);
	fails = fopen("../../fails", "w");
	zero_result();
	setvbuf(fails, NULL, _IONBF, 0);
	for(int i = 0; i < num_of_main_tests; i++)
	{
		r = new_differ_test(get_test_name(i, 1), get_code_name(i, 1));
		check_file(r, fails);
		close_differ_test(r);
	}
	printf("\n=== \\\\ Main results: [%6zu/%6zu]\n", total.num_of_tests - total.num_of_fails, total.num_of_tests);
	print_result(0);
	temp.num_of_tests = total.num_of_tests;
	temp.num_of_fails = total.num_of_fails;
	zero_result();
	for(int i = 0; i < num_of_bonus_tests; i++)
	{
		r = new_differ_test(get_test_name(i, 0), get_code_name(i, 0));
		check_file(r, fails);
		close_differ_test(r);
	}
	printf("\n=== \\\\ Bonus results: [%6zu/%6zu]\n", (total.num_of_tests - temp.num_of_tests) - (total.num_of_fails - temp.num_of_fails), total.num_of_tests - temp.num_of_tests);
	print_result(1);
	printf("Total number of tests: %zu\n", total.num_of_tests);
	printf("Total number of fails: %zu\n", total.num_of_fails);
	fclose(fails);
	return (0);
}
