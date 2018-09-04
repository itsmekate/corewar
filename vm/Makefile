CC = gcc
CFLAG = -Wall -Wextra -Werror
NAME = ../corewar
INCL = vm.h op.h
SRC = 	main.c \
		memory.c 
		##op.c
OBJ = $(SRC:.c=.o)
LIB = ../libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c $(INCL)
	$(CC) -c $(CFLAG) $< -o $@

clean:
	make -C ../libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C ../libft/ fclean
	rm -rf $(NAME)

$(LIB):
	make -C ../libft

re: fclean all