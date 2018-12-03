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

NAME = ../../asm
SRCS = main.c \
		get_name_comment.c \
		find_name_comment.c \
		create_file.c \
		create_command.c \
		op.c \
		validation_commands.c \
		validation_args.c \
		find_args.c \
		args_type.c \
		additional.c \
		additional1.c \
		a_bonus.c \

OBJ_DIR = ../../obj/
OBJ_ASM = $(OBJ_DIR)asm/
LIB = $(OBJ_DIR)libft/libft.a
OBJ = $(addprefix $(OBJ_ASM), $(SRCS:.c=.o))
INCL = op.h asm.h
CFLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address -g

all: $(NAME)

$(NAME): $(LIB) $(OBJ_ASM) $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o  $(NAME) $(LIB)

$(LIB): 
	make -C ../libft

clean:
	/bin/rm -f $(OBJ)
	make -C ../libft clean
	rm -rf $(OBJ_ASM)

fclean: clean
	/bin/rm -f $(NAME)
	make -C ../libft fclean

re: fclean all

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_ASM): $(OBJ_DIR)
	mkdir $(OBJ_ASM)

$(OBJ_ASM)%.o: %.c $(INCL)
	 gcc $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re libft

.NOTPARALLEL: all clean fclean re libft
