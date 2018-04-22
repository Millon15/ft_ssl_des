
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

void	skip_trash(t_line *tests)
{
	if (tests->str[0] != '=')
	do
		read_line(tests);
	while (tests->len > -1 && (tests->str[0] == '#' || tests->str[0] == '\0'));
	if (tests->str[0] != '=')
		bad_file();
	do
		read_line(tests);
	while (tests->len > -1 && (tests->str[0] == '#' || tests->str[0] == '\0'));
}

void	print_template(t_line *mkfile)
{
	fprintf(mkfile->fd, "\n#[n$] [flags] [width] [precision] [lengthes] [types]");
	fprintf(mkfile->fd, "\n#[args] [code piece] [do print something extra(for %%n)]\n");
}

void	print_list_to_makefile(size_t *n, t_line *mkfile, t_list *list, char *testtypes)
{
	*n = 0;
	
	fprintf(mkfile->fd, "\n# %s TESTS\n\n", testtypes);
	while (list)
	{
		fprintf(mkfile->fd, "TEST_%c%03zu = ", testtypes[0], *n);
		fprintf(mkfile->fd, "\"test_%c%03zu\" %s\n", testtypes[0] - 'A' + 'a', *n, list->str);
		list = list->next;
		*n = *n + 1;
	}
}

void	print_test_vars(t_line *mkfile, t_list **main_test_list, t_list **bonus_test_list,
						size_t *num_of_main_tests, size_t *num_of_bonus_tests)
{
	t_line	*tests;

	tests = new_readline("./tests", "r");
	skip_trash(tests);
	while (tests->len > 0 && tests->str[0] != '=')
	{	
		if (tests->str[0] == '\"')
			lst_push_back(main_test_list, lst_new(tests->str));
		read_line(tests);
	}
	print_list_to_makefile(num_of_main_tests, mkfile, *main_test_list, "MAIN");
	skip_trash(tests);
	while (tests->len > 0 && tests->str[0] != '=')
	{	
		if (tests->str[0] == '\"')
			lst_push_back(bonus_test_list, lst_new(tests->str));
		read_line(tests);
	}
	print_list_to_makefile(num_of_bonus_tests, mkfile, *bonus_test_list, "BONUS");
	close_readline(tests);
}

int		main(int ac, char **av)
{
	t_line	*mkfile;
	t_list	*main_test_list;
	t_list	*bonus_test_list;
	size_t	num_of_main_tests;
	size_t	num_of_bonus_tests;

	char	*testers;
	char	*exedir;
	char	*exetests;

	if (ac != 4)
		bad_input();
	testers = av[1];
	exedir = av[2];
	exetests = av[3];
	mkfile = new_readline(ft_strjoin(ft_strjoin("./resources/", testers), "/Makefile"), "w");
	print_template(mkfile);
	main_test_list = NULL;
	bonus_test_list = NULL;
	print_test_vars(mkfile, &main_test_list, &bonus_test_list, &num_of_main_tests, &num_of_bonus_tests);
	fprintf(mkfile->fd, "TEST_NAMES =");
	for (size_t i = 0; i < num_of_main_tests; i++)
		fprintf(mkfile->fd, " test_m%03zu", i);
	for (size_t i = 0; i < num_of_bonus_tests; i++)
		fprintf(mkfile->fd, " test_b%03zu", i);
	fprintf(mkfile->fd, "\nTESTERS_C = $(patsubst %%, .%s/%%.c, $(TEST_NAMES))", testers);


	fprintf(mkfile->fd, "\n\nTEST_EXE = $(patsubst %%, .%s/%%, $(TEST_NAMES))", exetests);
	fprintf(mkfile->fd, "\n\n# COLORS\n\nGREEN = \'\\033[0;32m\'\n");
	fprintf(mkfile->fd, "PURPLE = \'\\033[0;35m\'\nCYAN = \'\\033[0;36m\'\n");
	fprintf(mkfile->fd, "LGRAY = \'\\033[0;37m\'\nNC = \'\\033[0m\'");

	fprintf(mkfile->fd, "\n");

	fprintf(mkfile->fd, "\ncreate_testers:\n");
	for (size_t i = 0; i < num_of_main_tests; i++)
		fprintf(mkfile->fd, "\t@.%s/testmaker $(TEST_M%03zu) && printf \".\"\n", exedir, i);
	for (size_t i = 0; i < num_of_bonus_tests; i++)
		fprintf(mkfile->fd, "\t@.%s/testmaker $(TEST_B%03zu) && printf \".\"\n", exedir, i);
	fprintf(mkfile->fd, "\t@printf \"\\n\"\n");

	fprintf(mkfile->fd, "\n.%s/%%: .%s/%%.c\n", exetests, testers);
	fprintf(mkfile->fd, "\t@gcc -w -o $@ $< -I../.. -L../.. -lftprintf\n");
	fprintf(mkfile->fd, "\t@printf \".\"\n");

	fprintf(mkfile->fd, "\ncompiler: $(TEST_EXE)\n");

	fprintf(mkfile->fd, "\ncompile_testers:\n");
	fprintf(mkfile->fd, "\t@echo ${CYAN}\"[Compiling testers]\"${NC} May take long\n");
	fprintf(mkfile->fd, "\t@make compiler\n");
	fprintf(mkfile->fd, "\t@printf \"\\n\"\n");

	fprintf(mkfile->fd, "\nrun_testers:\n");
	fprintf(mkfile->fd, "\t@echo ${PURPLE}\"[Running testers]\"${NC} \"Shouldn\'t take long! \"${LGRAY}\"[except some last long tests]\"${NC}\n");
	for (size_t i = 0; i < num_of_main_tests; i++)
		fprintf(mkfile->fd, "\t@.%s/test_m%03zu > ../testing_results/test_m%03zu_ft_printf_print && printf %zu || printf \"x\"\n", exetests, i, i, i % 10);
	fprintf(mkfile->fd, "\t@printf \"|\"\n");
	for (size_t i = 0; i < num_of_bonus_tests; i++)
		fprintf(mkfile->fd, "\t@.%s/test_b%03zu > ../testing_results/test_b%03zu_ft_printf_print && printf %zu || printf \"x\"\n", exetests, i, i, i % 10);
	fprintf(mkfile->fd, "\t@printf \"\\n\"\n");

	fprintf(mkfile->fd, "\ndiff:\n");
	fprintf(mkfile->fd, "\t@echo ${PURPLE}\"[Running difference check]\"${NC}\n");
	fprintf(mkfile->fd, "\t@rm ../../fails || true\n");
	fprintf(mkfile->fd, "\t@.%s/check_difference \"%zu\" \"%zu\"", exedir, num_of_main_tests, num_of_bonus_tests);
	fprintf(mkfile->fd, "\n");
	close_readline(mkfile);
	return (0);
}
