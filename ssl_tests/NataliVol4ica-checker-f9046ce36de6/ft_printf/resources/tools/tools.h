
#ifndef TOOLS_H
# define TOOLS_H

# include <string.h>
# include "structs.h"

# define P_PRINT "printf_print"
# define P_RET   "printf_ret"
# define F_PRINT "ft_printf_print"
# define F_RET "ft_printf_ret"

//	FILE TOOLS

t_line	*new_readline(char *file, char *flags); //new t_line
void	close_readline(t_line *l);	//close and delete t_line
int		read_line(t_line *line);	//read the line
int		read_delim(t_line *line, char delim);	//read the line until delimeter
void	skip_read_line(t_line *l, int n);	//skip N getlines
void	skip_read_delim(t_line *l, char delim, int n);	//skip N getdelims

// LIST TOOLS

t_list	*lst_new(char *str);	//creates new list element
void	lst_push_back(t_list **list, t_list *elem);	//add list elem to the end of list

//	DEFAULT TOOLS

char	*ft_strnew(int n);
size_t	ft_strlen(const char *str);	//length of string
char	*ft_strdup(const char *str);	//duplicate str
char	*ft_strjoin(char const *s1, char const *s2);	//concatenates two strings
char	**ft_strsplit(char const *s, size_t *n, char c);	//splits str into **words

//	ERRORS

void	bad_malloc(void);
void	bad_file(void);
void	bad_input(void);

//	DIFFERERS

char			*get_test_name(int n, int ismain);
char			*get_code_name(int n, int ismain);
t_read_lines	*new_differ_test(char *name, char *code_file);
void			close_differ_test(t_read_lines *r);

// RESULT FUNCS

void			zero_result(void);
void			print_result(int is_bonus);

#endif
