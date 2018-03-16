AS=yasm
CC=gcc
LD=ld
drivers_TARGETS=int.elf disk.elf time.elf stdio.elf gdt.elf
%.o:	%.c
	${CC} -Wno-implicit-function-declaration -g -ffreestanding -nostdlib -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	${AS} -felf $< -o $@
