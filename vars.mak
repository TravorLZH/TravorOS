AS=yasm
CC=gcc
%.o:	%.c
	${CC} -g -ffreestanding -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	${AS} -felf $< -o $@
