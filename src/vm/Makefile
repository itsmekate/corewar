CC = gcc
CFLAG = -Wall -Wextra -Werror
NAME = ../../corewar
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
		log2.c \
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
OBJ_DIR = ../../obj/
OBJ_VM = $(OBJ_DIR)vm/
VISUAL_FLAG = -lncurses
VISUAL_SRC =  ncurses.c ncurses2.c ncurses3.c ncurses4.c
OBJ = $(addprefix $(OBJ_VM), $(SRC:.c=.o))
VISUAL_OBJ = $(addprefix $(OBJ_VM), $(VISUAL_SRC:.c=.o))
LIB = ../libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ_VM) $(OBJ) $(VISUAL_OBJ)
	$(CC) $(OBJ) $(LIB) $(VISUAL_FLAG) $(VISUAL_OBJ) -o $(NAME) 

$(LIB):
	make -C ../libft

$(OBJ_VM)%.o: %.c $(INCL)
	$(CC) -c $(CFLAG) $< -o $@

clean:
	make -C ../libft/ clean
	rm -rf $(OBJ)
	rm -rf $(VISUAL_OBJ)
	rm -rf $(OBJ_VM)

fclean: clean
	make -C ../libft/ fclean
	rm -rf $(NAME)

$(OBJ_VM): $(OBJ_DIR)
	mkdir -p $(OBJ_VM)
	mkdir -p $(OBJ_VM)functions

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


re: fclean all