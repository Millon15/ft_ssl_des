# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/03/10 13:08:31 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ssl
LIB		=	libft/
SRC_D	=	src/
SRC		=	ft_ssl.c \
			read_args.c \
			error.c \
			$(SRC_D)base64.c \
			$(SRC_D)put_des.c \
			$(SRC_D)des.c \
			$(SRC_D)des3.c
OBJ_D	=	obj/
OBJ		=	$(addprefix $(OBJ_D), $(SRC:.c=.o))
LFLAGS	=	-lft -L $(LIB)
IFLAGS	=	-I $(LIB) -I ./
CFLAGS	=	-Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB)
	gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LFLAGS)

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o: %.c
	gcc $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make clean -C $(LIB)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_D)
	make fclean -C $(LIB)

re: fclean all

.PHONY: all clean fclean re
