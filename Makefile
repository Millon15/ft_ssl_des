# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/02/01 19:20:40 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ssl
LIB		=	ft_printf/libftprintf.a
SRC		=	ft_ssl.c \
			read_args.c \
			error.c \
			src/base64.c \
			src/des_ecb.c

OBJ		=	$(SRC:.c=.o)
CFLAGS	=	
# CFLAGS	=	-Wall -Wextra -Werror


all: $(LIB) $(NAME)

$(LIB): 
	make -C ft_printf/

$(NAME): $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $^ $(LIB)

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	make clean -C ft_printf/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ft_printf/
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
