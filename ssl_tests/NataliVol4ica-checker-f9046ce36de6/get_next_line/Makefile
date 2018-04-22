#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 15:33:35 by nkolosov          #+#    #+#              #
#    Updated: 2017/11/16 15:33:35 by nkolosov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

FOLD = .

# GNL FILES

GNLC = $(FOLD)/get_next_line.c
GNLH = $(FOLD)/get_next_line.h
GNLO = $(FOLD)/get_next_line.o

# FOLDERS

RESOURCES = ./resources
TESTFOLD = $(RESOURCES)/tests
SHDIR = $(RESOURCES)/scripts

BASICDIR = ./00.basic_tests
MIDDIR = ./01.middle_tests
ADVDIR = ./02.advanced_tests
ERRDIR = ./03.error_tests
BONUSDIR = ./04.bonus_tests

BD = $(TESTFOLD)/$(BASICDIR)
MD = $(TESTFOLD)/$(MIDDIR)
AD = $(TESTFOLD)/$(ADVDIR)
ED = $(TESTFOLD)/$(ERRDIR)
BND = $(TESTFOLD)/$(BONUSDIR)

EXEDIR = $(RESOURCES)/exe
LOGDIR = $(RESOURCES)/logs

MAINDIR = $(RESOURCES)/mains

# NAMES

NAME = $(EXEDIR)/test_gnl_file
NAME2 = $(EXEDIR)/test_gnl_std
NAME3 = $(EXEDIR)/test_gnl_error
NAME4 = $(EXEDIR)/test_gnl_ds

LIBDIR = $(FOLD)/libft
LIBFT = $(LIBDIR)/libft.a

NAMES = $(NAME) $(NAME2) $(NAME3) $(NAME4)

# MAIN FILES

MAIN1 = $(MAINDIR)/main
MAIN2 = $(MAINDIR)/main2
MAIN3 = $(MAINDIR)/main3
MAIN4 = $(MAINDIR)/main4

# BASH SCRIPTS

RUN_S = sh $(SHDIR)/run_s.sh
RUN_F = sh $(SHDIR)/run_f.sh
RUN_ERR = sh $(SHDIR)/run_err.sh
RUN_BONUS = sh $(SHDIR)/run_bonus.sh

RUNANS_S = sh $(SHDIR)/runans_s.sh
RUNANS_F = sh $(SHDIR)/runans_f.sh
RUNANS_ERR = sh $(SHDIR)/runans_err.sh
RUNANS_BONUS = sh $(SHDIR)/runans_bonus.sh

# BASIC TESTS

T8_S =		8_test0 \
			8_test1 \
			8_test2
T8_F =		8_test3 \
			8_test4 \
			8_test5
T8C_F = $(patsubst %, $(RUN_F) $(NAME) $(BD) % ;, $(T8_F))
T8C_S = $(patsubst %, $(RUN_S) $(NAME2) $(BD) % ;, $(T8_S))

# MIDDLE TESTS

T16_F =		16_test0 \
			16_test1 \
			16_test2 
T16_S =		16_test3 \
			16_test4 \
			16_test5 
T16C_F = $(patsubst %, $(RUN_F) $(NAME) $(MD) % ;, $(T16_F))
T16C_S = $(patsubst %, $(RUN_S) $(NAME2) $(MD) % ;, $(T16_S))

# ADVANCED TESTS

T4_F =		4_test0 \
			4_test1 \
			4_test2
T4_S =		4_test3 \
			4_test4 \
			4_test5
T4_E = 		4_test6 \
			8_test7 \
			16_test8 \
			long1 \
			long2 \
			long3 \
			empty0 \
			empty1
T4C_F = $(patsubst %, $(RUN_F) $(NAME) $(AD) % ;, $(T4_F))
T4C_S = $(patsubst %, $(RUN_S) $(NAME2) $(AD) % ;, $(T4_S))
T4C_E = $(patsubst %, $(RUN_F) $(NAME) $(AD) % ;, $(T4_E))

# BONUS TESTS

T_B = 	text1 \
		text2 \
		text3
TB_C = $(RUN_BONUS) $(NAME4) $(BND) $(T_B)

# COMMANDS FOR GETTING CORRECT ANSWERS

AT8C_F = $(patsubst %, $(RUNANS_F) $(NAME) $(BD)/% ;, $(T8_F))
AT8C_S = $(patsubst %, $(RUNANS_S) $(NAME2) $(BD)/% ;, $(T8_S))
AT16C_F = $(patsubst %, $(RUNANS_F) $(NAME) $(MD)/% ;, $(T16_F))
AT16C_S = $(patsubst %, $(RUNANS_S) $(NAME2) $(MD)/% ;, $(T16_S))
AT4C_F = $(patsubst %, $(RUNANS_F) $(NAME) $(AD)/% ;, $(T4_F))
AT4C_S = $(patsubst %, $(RUNANS_S) $(NAME2) $(AD)/% ;, $(T4_S))
AT4C_E = $(patsubst %, $(RUNANS_F) $(NAME) $(AD)/% ;, $(T4_E))
AT_E = $(RUNANS_ERR) $(NAME3) $(TESTFOLD)/$(ERRDIR)
AT_B = $(RUNANS_BONUS) $(NAME4) $(BND) $(T_B)

# COLORS

RED = '\033[0;31m'
GREEN = '\033[0;32m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

# BUILD COMMANDS

all:
	sh $(SHDIR)/help.sh

full:
	@make $(NAME)
	@make $(NAME2)
	@make $(NAME3)
	@make $(NAME4)	

libre:
	@mkdir $(LOGDIR) || true
	make -C $(LIBDIR)/ fclean > $(LOGDIR)/lib_fclean
	make -C $(LIBDIR)/ > $(LOGDIR)/lib_make

$(NAME): $(GNLO) $(MAIN1).o $(GNLH) $(LIBFT)
	clang -o $(NAME) $(MAIN1).o $(GNLO) -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft

$(NAME2): $(GNLO) $(MAIN2).o $(GNLH) $(LIBFT)
	clang -o $(NAME2) $(MAIN2).o $(GNLO) -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft

$(NAME3): $(GNLO) $(MAIN3).o $(GNLH) $(LIBFT)
	clang -o $(NAME3) $(MAIN3).o $(GNLO) -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft

$(NAME4): $(GNLO) $(MAIN4).o $(GNLH) $(LIBFT)
	clang -o $(NAME4) $(MAIN4).o $(GNLO) -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft

$(GNLO): $(GNLC) $(GNLH) $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(GNLO) -c $(GNLC)

$(MAIN1).o: $(MAIN1).c $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(MAIN1).o -c $(MAIN1).c

$(MAIN2).o: $(MAIN2).c $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(MAIN2).o -c $(MAIN2).c

$(MAIN3).o: $(MAIN3).c $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(MAIN3).o -c $(MAIN3).c

$(MAIN4).o: $(MAIN4).c $(LIBFT)
	clang -Wall -Wextra -Werror -I $(LIBDIR)/includes -o $(MAIN4).o -c $(MAIN4).c

$(LIBFT):
	@make -C $(LIBDIR)/

fold:
	@sh $(SHDIR)/set_fold.sh $(FOLD)

clean:
	@find $(RESOURCES)/ -name "*.o" -delete
	@touch 1.o
	@rm *.o

fclean: clean
	@rm $(NAMES) || true

re: fclean full

norm:
	@clear
	@norminette $(GNLC) $(GNLH)
	@norminette $(LIBDIR)/ || true

# TESTING COMMANDS

test_basic: $(NAMES)
	@mkfile 0 $(BD)/total_temp
	@mkfile 0 $(BD)/total
	@echo ${CYAN}[Basic tests]${NC}
	@$(T8C_S)
	@$(T8C_F)
	@sh $(SHDIR)/print_res.sh $(BD)
	@rm $(BD)/total_temp

test_middle: $(NAMES)
	@mkfile 0 $(MD)/total_temp
	@mkfile 0 $(MD)/total
	@echo ${CYAN}[Middle tests]${NC}
	@$(T16C_F)
	@$(T16C_S)
	@sh $(SHDIR)/print_res.sh $(MD)
	@rm $(MD)/total_temp

test_advanced: $(NAMES)
	@mkfile 0 $(AD)/total_temp
	@mkfile 0 $(AD)/total
	@echo ${CYAN}[Advanced tests]${NC}
	@$(T4C_F)
	@$(T4C_S)
	@$(T4C_E)
	@sh $(SHDIR)/print_res.sh $(AD)
	@rm $(AD)/total_temp

test_error: $(NAMES)
	@mkfile 0 $(ED)/total_temp
	@mkfile 0 $(ED)/total
	@echo ${CYAN}[Error management]${NC}
	@$(RUN_ERR) $(NAME3) $(TESTFOLD)/$(ERRDIR)
	@sh $(SHDIR)/print_res.sh $(ED)
	@rm $(ED)/total_temp

test_bonus: $(NAMES)
	@mkfile 0 $(BND)/total_temp
	@mkfile 0 $(BND)/total
	@echo ${CYAN}[Bonus part]${NC}
	@$(TB_C)
	@sh $(SHDIR)/print_res.sh $(BND)
	@rm $(BND)/total_temp

test_all: $(NAMES)
	@make test_basic
	@make test_middle
	@make test_advanced
	@make test_error
	@make test_bonus
	@echo "   [Basic tests]" > $(LOGDIR)/eval
	@cat $(BD)/total >> $(LOGDIR)/eval
	@echo "\n   [Middle tests]" >> $(LOGDIR)/eval
	@cat $(MD)/total >> $(LOGDIR)/eval
	@echo "\n   [Advanced tests]" >> $(LOGDIR)/eval
	@cat $(AD)/total >> $(LOGDIR)/eval
	@echo "\n   [Error tests]" >> $(LOGDIR)/eval
	@cat $(ED)/total >> $(LOGDIR)/eval
	@echo "\n   [Bonus tests]" >> $(LOGDIR)/eval
	@cat $(BND)/total >> $(LOGDIR)/eval

eval_gans: $(NAMES)
	@$(AT8C_F)
	@$(AT8C_S)
	@$(AT16C_F)
	@$(AT16C_S)
	@$(AT4C_F)
	@$(AT4C_S)
	@$(AT4C_E)
	@$(AT_E)
	@$(AT_B)

tclean: aclean
	@find . -name "*_cor" -delete

aclean:
	@find . -name "*_ans" -delete

evalclean:
	@make fclean
	@make -C libft/ clean
	@make aclean
	@rm -rf $(LOGDIR) || true
	@find $(RESOURCES) -name "total*" -delete

# EVAL COMMAND

eval:
	@clear
	@tar -cf Makefile.tar Makefile
	@rm *.tar
	@cat $(RESOURCES)/files/header
	@echo ${BLUE}"                   >>>>>>|| TESTING GET_NEXT_LINE ||<<<<<<\n"${NC}
	@echo ${PURPLE}"===================>>>>>>||  Files in directory:  ||<<<<<<==================="${NC}
	@ls -l > files
	@./$(EXEDIR)/checker_ls
	@rm files
	@echo ${PURPLE}"===================>>>>>>||      Author file:     ||<<<<<<==================="${NC}
	@cat -e $(FOLD)/author || cat -e $(FOLD)/auteur || echo ${RED}"NO AUTHOR FILE"${NC}
	@echo ${PURPLE}"===================>>>>>>||    get_next_line.h:   ||<<<<<<==================="${NC}
	@tail -n+13 $(GNLH)
	@echo ${PURPLE}"===================>>>>>>||     [NORM] Errors:    ||<<<<<<==================="${RED}
	@norminette $(GNLC) $(GNLH) > norm && norminette $(LIBDIR)/ >> norm && grep "Error " < norm > norm2 && cat norm2 && sh $(SHDIR)/norm_ok.sh && rm norm norm2 || rm norm && echo "norminette not found" 
	@echo ${PURPLE}"===================>>>>>>||    Static testing:    ||<<<<<<==================="${NC}
	@./$(EXEDIR)/checker_static
	@echo ${PURPLE}"===================>>>>>>||     Compiling lib:    ||<<<<<<==================="${NC}
	@make libre
	@echo ${PURPLE}"===================>>>>>>||     Compiling GNL:    ||<<<<<<==================="${NC}
	make full > $(LOGDIR)/gnl
	@echo ${PURPLE}"===================>>>>>>||        Testing:       ||<<<<<<==================="${NC}
	@make test_all

evalres:
	@-less $(LOGDIR)/eval || echo "Evaluation log has been removed or haven't been created yet."

tar:
	@make evalclean
	tar -cf check.tar resources/ Makefile

cc:
	#gcc checker_static.c -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft $(GNLC) -o checker_static
	#gcc checker_ls.c -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft $(GNLC) -o checker_ls
	#gcc checker_buffsize.c -I $(LIBDIR)/includes -L $(LIBDIR)/ -lft $(GNLC) -o checker_buffsize

help:
	@sh $(SHDIR)/help.sh
