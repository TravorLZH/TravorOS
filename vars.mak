AS=yasm -DMINGW
CC=gcc
LD=i386-elf-ld
%.o:	%.c
	@echo "Compiling $^"
	@${CC} -g -ffreestanding -nostdlib -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	@echo "Assembling $^"
	@${AS} -felf $< -o $@
