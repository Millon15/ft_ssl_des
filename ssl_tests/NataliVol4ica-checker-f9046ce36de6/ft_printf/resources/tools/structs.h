
#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdio.h>

typedef struct	s_line
{
	char	*filename;
	char	*str;
	int		len;
	FILE	*fd;
}				t_line;

typedef struct	s_read_lines
{
	t_line		*printf_line;
	t_line		*printf_ret;
	t_line		*ft_printf_line;
	t_line		*ft_printf_ret;
	t_line		*source_code;
}				t_read_lines;

typedef struct		s_list
{
	char			*str;
	struct s_list	*next;
}					t_list;

typedef struct	s_test
{
	char	*name;
	FILE	*fd;
	char	*fdname;
	char	*n;
	char	*flags;
	size_t	numof_flags;
	size_t	numof_flagcombinations;
	char	*width;
	char	*precision;
	char	**lengthes;
	size_t	numof_lengthes;
	char	*types;
	size_t	numof_types;
	char	*args;
	char	*extra_code;
	char	*extra_print;
	//
	char	flagmass[6];
	char	type;
	char	*length;
	size_t	testnum;
}				t_test;

typedef struct	s_result_info
{
	size_t	num_of_tests;
	size_t	num_of_fails;
}				t_result_info;

enum m_types
{
	td = 0, tD, ti, to, tO, tu, tU, tx, tX, tc, tC, ts, tS, tp, tperc, tmmax //15
};

enum b_types
{
	te = 0, tE, tf, tF, ta, tA, tg, tG, tn, tbmax //9
};

enum lens
{
	lnone = 0, lhh, lh, ll, lll, lj, lz, lL, lt //9
};

typedef struct	s_result
{
	t_result_info	main_values[15][9];
	t_result_info	bonus_values[9][9];
	t_result_info	apostrophe;
	t_result_info	stars;
	t_result_info	dollar;
}				t_result;

t_result		result;
t_result_info	total;
t_result_info	temp;

#endif
