NAME = Corewar
SRC = src/
OBJ = obj/
ASM = $(SRC)asm
VM = $(SRC)vm
LIB = $(SRC)libft

all: $(NAME)

$(NAME):
	make -C $(LIB)
	make -C $(ASM)
	make -C $(VM)

clean:
	make -C $(ASM) clean
	make -C $(VM) clean
	rm -rf $(OBJ)

fclean:
	make -C $(ASM) fclean
	make -C $(VM) fclean
	rm -rf $(OBJ)
	find . -name "*.cor" > cor
	rm -f `cat cor`
	rm -f cor

re: fclean all