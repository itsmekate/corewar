BASM = asm
BVM = corewar
BLIB = libft
SRC = src/
OBJ = obj/
ASM = $(SRC)asm
VM = $(SRC)vm
LIB = $(SRC)libft

all: $(BLIB) assembl vm

$(BLIB):
	make -C $(LIB)

assembl:
	make -C $(ASM)

vm:
	make -C $(VM)

$(BVM): vm

$(BASM): assembl

clean:
	make -C $(ASM) clean
	make -C $(VM) clean
	rm -rf $(OBJ)

fclean:
	make -C $(ASM) fclean
	make -C $(VM) fclean
	rm -rf $(OBJ)
	@find . -name "*.cor" > cor
	@rm -f `cat cor`
	@rm -f cor

re: fclean all