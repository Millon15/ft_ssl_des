# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/02/04 15:35:35 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ssl
LIB_C	=	libft/
LIB		=	$(LIB_C)libft.a
SRC		=	ft_ssl.c \
			read_args.c \
			error.c \
			src/base64.c \
			src/des_ecb.c

OBJ		=	$(SRC:.c=.o)
CFLAGS	=	
# CFLAGS	=	-Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LIB)

$(LIB): 
	make -C $(LIB_C)

%.o: %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	make clean -C $(LIB_C)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB_C)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
