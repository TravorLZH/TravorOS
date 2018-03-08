AS=yasm
CC=i386-elf-gcc
LD=i386-elf-ld
drivers_TARGETS=int.elf disk.elf time.elf stdio.elf
%.o:	%.c
	${CC} -Wno-implicit-function-declaration -g -ffreestanding -nostdlib -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	${AS} -felf $< -o $@
