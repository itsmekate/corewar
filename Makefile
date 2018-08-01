# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kprasol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/26 14:32:41 by kprasol           #+#    #+#              #
#    Updated: 2018/07/12 19:58:47 by kprasol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS = read.c \
		create_file.c \
		create_command.c \
		op.c \

LIB = -L libft/ -lft
OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

all: $(NAME)

libft: 
	make -C ./libft

$(NAME): libft $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o  $(NAME)  $(LIB) -I ./

clean:
	/bin/rm -f $(OBJ)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

%.o: %.c
	 gcc $(CFLAGS) -c -o  $@ $< -I ./libft

.PHONY: all clean fclean re libft

.NOTPARALLEL: all clean fclean re libft
