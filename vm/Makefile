CC = gcc
CFLAG = -Wall -Wextra -Werror
NAME = ../corewar
INCL = vm.h op.h
SRC = 	main.c \
		memory.c \
		memory2.c \
		init.c \
		init2.c \
		player.c \
		point.c \
		number.c \
		info.c \
		cycle.c \
		log.c \
		cycle_to_die.c \
		functions/addition.c functions/aff.c \
		functions/ft_and.c functions/ft_fork.c \
		functions/ft_or.c functions/ft_xor.c \
		functions/live.c functions/load.c \
		functions/load_index.c functions/long_fork.c \
		functions/long_load.c functions/long_load_index.c \
		functions/store.c functions/store_index.c \
		functions/substraction.c functions/zjump.c \
		functions/functions.c \
		output.c
		##op.c
VISUAL_FLAG = -lncurses
VISUAL_SRC =  ncurses.c ncurses2.c ncurses3.c
OBJ = $(SRC:.c=.o)
LIB = ../libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(OBJ) $(LIB) $(VISUAL_FLAG) $(VISUAL_SRC) -o $(NAME) 

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