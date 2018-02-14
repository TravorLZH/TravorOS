AS=yasm
CC=gcc
%.o:	%.c
	@echo "Compiling $^"
	@${CC} -g -ffreestanding -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	@echo "Assembling $^"
	@${AS} -felf $< -o $@
