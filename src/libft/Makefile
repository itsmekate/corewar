# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kprasol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/26 14:32:41 by kprasol           #+#    #+#              #
#    Updated: 2017/11/16 19:30:19 by kprasol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c \
ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c \
ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
ft_list_size.c ft_list_reverse.c ft_list_last.c ft_list_clear.c ft_swap.c get_next_line.c \
		main.c \
		struct.c \
		ft_put.c \
		itoa_base.c \
		unicode.c \
		print.c \
		count_digits.c \
		print_cs.c \
		print_ou.c \
		print_di.c \
		print_px.c \
		check_line.c \
		ft_itoa_base.c \
		ft_mleak.c
OBJ_DIR = ../../obj/

OBJ_LIB = $(OBJ_DIR)libft/
NAME = libft.a
FLAGS = -Wall -Wextra -Werror
OBJ = $(addprefix $(OBJ_LIB), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_LIB) $(OBJ)
	ar rc  $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_LIB): $(OBJ_DIR)
	mkdir -p $(OBJ_LIB)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_LIB)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_LIB)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re
