AS=yasm
CC=gcc
LD=ld
drivers_TARGETS=int.elf time.elf stdio.elf gdt.elf
CPPFLAGS=-ffreestanding -nostdlib
CFLAGS=-Wno-implicit-function-declaration -Wno-packed-bitfield-compat -g -m32
%.o:	%.c
	${CC} $(CFLAGS) $(CPPFLAGS) $(INCLUDE_DIR) -c $< -o $@
%.o:	%.asm
	${AS} -felf $< -o $@
