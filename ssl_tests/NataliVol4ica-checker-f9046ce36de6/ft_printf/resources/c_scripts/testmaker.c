
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libc.h>
#include "tools.h"

#define TESTPATH "../generated_testers/"

#define UNDEF 0 //are undefined behavior tests allowed
#define APOST_TYPES "dDuUifF" // 7
#define NONDEFLEN_TYPES "cCsSp%" // 6
#define L_TYPES "aAeEfFgG" // 8

int		is_flag_available(char flag, t_test *t)
{
	size_t	i;

	for (i = 0; i < t->numof_flags; i++)
		if (t->flags[i] == flag)
			break;
	if (i == t->numof_flags)
		return (0);
	return (t->flagmass[i]);
}

int		is_len_available(char *len, t_test *t)
{
	if (!len && !t->length[0])
		return (1);
	if (!len)
		return (0);
	for (int i = 0; i < strlen(len); i++)
		if (len[i] != t->length[i])
			return (0);
	return (1);
}

int		is_undef(t_test *t)
{
	size_t	i;

	if (UNDEF)
		return (0);
	if (t->precision && t->precision[1] != '\0' && t->type == 'p')
		return (1);
	if (is_flag_available('0', t) && t->type == 'n')
		return (1);
	if (is_flag_available('\'', t))
	{
		for (i = 0; i < 7; i++)
			if (t->type == APOST_TYPES[i])
				break;
		if (i == 7)
			return (1);
	}
	if (t->length && (t->type == '%' || t->type == 'p'))
		return (1);
	if (t->length && t->length[0] == 'l' && (t->type == 'C' || t->type == 'S'))
		return (1);
	if (t->length && !(t->length[0] == 'l' && t->length[1] == '\0'))
		for (i = 0; i < 6; i++)
			if (t->type == NONDEFLEN_TYPES[i])
				return (1);
	if (t->length && t->length[0] != 'L' && t->length[0] != 't' && !(t->length[0] == 'l' && t->length[1] != 'l'))
	{
		for (i = 0; i <8; i++)
			if (t->type == L_TYPES[i])
				break;
		if (i < 8)
			return (1);
	}
	return (0);
}

void	set_flags(t_test *t, size_t num)
{
	size_t i;

	for (i = 0; i < t->numof_flags; i++)
		t->flagmass[i] = 0;
	i = 0;
	while (num > 0)
	{
		t->flagmass[i++] = num % 2;
		num /= 2;
	}
}

void	print_flags(t_test *t)
{
	for (size_t i = 0; i < t->numof_flags; i++)
		if (t->flagmass[i])
			fprintf(t->fd, "%c", t->flags[i]);
}

void	print_test(t_test *t)
{
	if (is_undef(t))
		return ;
	fprintf(t->fd, "//@\n");
	fprintf(t->fd, "\tft_printf(\"\\n#%04zu\");\n", t->testnum);
	fprintf(t->fd, "\tfprintf(printf_, \"\\n#%04zu\");\n", t->testnum);

	fprintf(t->fd, "\tret1 = fprintf(printf_, \"|%%%s", t->n);
	print_flags(t);
	fprintf(t->fd, "%s%s", t->width, t->precision);
	if (t->length) fprintf(t->fd, "%s", t->length);
	fprintf(t->fd, "%c|", t->type);
	if (t->extra_print[0]) fprintf(t->fd, "%%n");
	fprintf(t->fd, "\"");
	if (t->args[0] != '\0') fprintf(t->fd, ", %s", t->args);
	fprintf(t->fd, ");");

	if (t->extra_print[0])
		fprintf(t->fd, "fprintf(printf_,\"%%d|\", %s); %s = 0;\n", t->extra_print, t->extra_print);
	else
		fprintf(t->fd, "\n");

	fprintf(t->fd, "\tret2 = ft_printf(\"|%%%s", t->n);
	print_flags(t);
	fprintf(t->fd, "%s%s", t->width, t->precision);
	if (t->length) fprintf(t->fd, "%s", t->length);
	fprintf(t->fd, "%c|", t->type);
	if (t->extra_print[0]) fprintf(t->fd, "%%n");
	fprintf(t->fd, "\"");
	if (t->args[0] != '\0') fprintf(t->fd, ", %s", t->args);
	fprintf(t->fd, ");");
	
	if (t->extra_print[0])
		fprintf(t->fd, "ft_printf(\"%%d|\", %s); %s = 0;\n", t->extra_print, t->extra_print);
	else
		fprintf(t->fd, "\n");
	
	fprintf(t->fd, "\tfprintf(printf_ret, \"%%d\\n\", ret1);\n");
	fprintf(t->fd, "\tfprintf(ft_printf_ret, \"%%d\\n\", ret2);\n");
	fprintf(t->fd, "\tif (ret1 == -1) {printf_ = fopen(\"../testing_results/%s_printf_print\", \"a\"); setvbuf(printf_, NULL, _IONBF, 0);}\n", t->name);
	t->testnum++;
}

void	print_tests(t_test *t)
{
	for (size_t flags = 0; flags < t->numof_flagcombinations; flags++)
	{
		set_flags(t, flags);
		for (size_t type = 0; type < t->numof_types; type++)
		{
			t->type = t->types[type];
			for (size_t length = 0; length < t->numof_lengthes; length++)
			{
				t->length = t->lengthes[length];
				t->length = t->length[0] == '-' ? '\0' : t->length;
				
				print_test(t);
			}
		}
	}
}

void	print_main(t_test *t)
{
	fprintf(t->fd, "int\t\tmain(void)\n");
	fprintf(t->fd, "{\n");
	fprintf(t->fd, "\tFILE\t*printf_, *printf_ret, *ft_printf_ret;\n");
	fprintf(t->fd, "\tint\t\tret1, ret2;\n");
	fprintf(t->fd, "\n");

	fprintf(t->fd, "\tprintf_ = fopen(\"../testing_results/%s_printf_print\", \"w\");\n", t->name);
	fprintf(t->fd, "\tprintf_ret = fopen(\"../testing_results/%s_printf_ret\", \"w\");\n", t->name);
	fprintf(t->fd, "\tft_printf_ret = fopen(\"../testing_results/%s_ft_printf_ret\", \"w\");\n", t->name);
	fprintf(t->fd, "\tsetvbuf(printf_, NULL, _IONBF, 0);\n");
	fprintf(t->fd, "\tsetvbuf(printf_ret, NULL, _IONBF, 0);\n");
	fprintf(t->fd, "\tsetvbuf(ft_printf_ret, NULL, _IONBF, 0);\n");
	fprintf(t->fd, "\n");
	fprintf(t->fd, "\t%s\n", t->extra_code);
	print_tests(t);
	fprintf(t->fd, "\tfclose(printf_);\n");
	fprintf(t->fd, "\tfclose(printf_ret);\n");
	fprintf(t->fd, "\tfclose(ft_printf_ret);\n");
	fprintf(t->fd, "\treturn (0);\n");
	fprintf(t->fd, "}\n\n");
}

void	print_includes(t_test *t)
{
	fprintf(t->fd, "#include \"../tools/test_headers.h\"\n");
	fprintf(t->fd, "#include \"libftprintf.h\"\n\n");
}

void	set_param(char **ptr, char *av, size_t *len)
{
	if (av[0] == '\0' || (av[0] == '-' && av[1] == '\0'))
		*ptr = ft_strnew(0);
	else
		*ptr = av;
	if (len)
		*len = strlen(*ptr);
}

t_test *set_test(char **av)
{
	t_test	*t;

	if (!(t = (t_test*)malloc(sizeof(t_test)))) bad_malloc();
	t->name = av[0];
	t->fd = fopen(ft_strjoin(ft_strjoin(TESTPATH, av[0]), ".c"), "w");
	set_param(&t->n, av[1], NULL);
	set_param(&t->flags, av[2], &t->numof_flags);
	t->numof_flagcombinations = 1;
	for (size_t i = 0; i < t->numof_flags; i++)
		t->numof_flagcombinations *= 2;
	set_param(&t->width, av[3], NULL);
	set_param(&t->precision, av[4], NULL);
	t->lengthes = ft_strsplit(av[5], &t->numof_lengthes, '|');
	set_param(&t->types, av[6], &t->numof_types);
	if (t->numof_types == 0) bad_input();
	set_param(&t->args, av[7], NULL);
	set_param(&t->extra_code, av[8], NULL);
	set_param(&t->extra_print, av[9], NULL);
	t->testnum = 0;
	return (t);
}

int		main(int ac, char **av)
{
	t_test	*t;

	if (ac != 11)
		return (1);
	t = set_test(&av[1]);
	print_includes(t);
	print_main(t);
	fclose(t->fd);
	return (0);
}
