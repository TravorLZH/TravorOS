AS=yasm
CC=gcc
LD=ld
drivers_TARGETS=int.elf disk.elf time.elf stdio.elf gdt.elf
CFLAGS=-Wno-implicit-function-declaration -Wno-packed-bitfield-compat -g -ffreestanding -nostdlib -m32
%.o:	%.c
	${CC} $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@
%.o:	%.asm
	${AS} -felf $< -o $@
