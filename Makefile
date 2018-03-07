AS=yasm
CC=i386-elf-gcc -Wno-implicit-function-declaration
LD=i386-elf-ld

C_SOURCES=$(wildcard drivers/*.c kernel/*.c mm/*.c)
ASM_SOURCES=$(wildcard drivers/*.asm kernel/*.asm mm/*.asm)
BOOT_SRC=$(wildcard boot/*.asm)
INCLUDE_DIR=-Iinclude
kernel_LIBS=lib/libc.a
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}
libc_SOURCES=$(wildcard lib/*.c lib/*.asm)
libc_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(libc_SOURCES)));

%.o:	%.c
	${CC} -g -ffreestanding -nostdlib -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	${AS} -felf $< -o $@
.PHONY:	clean all run debug
all:	os.img kernel.elf
run:	os.img
	qemu-system-i386 -fda os.img -device isa-debug-exit,iobase=0xF4,iosize=0x04
debug:	os.img kernel.elf
	exec gdb -tui -x debug.gdb
os.img:	boot/boot.img kernel.bin $(kernel_LIBS)
	cat boot/boot.img kernel.bin > os.img
kernel.bin:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	$(LD) -melf_i386 -o $@ -e0x1000 -Ttext 0x1000 $^ --oformat binary
kernel.elf:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	$(LD) -melf_i386 -o $@ -emain -Ttext 0x1000 $^
drivers/interrupt.o:	drivers/interrupt.asm
boot/boot.img:
	(cd boot;make)
lib/libc.a:	$(libc_OBJ)
	ar rc $@ $^
clean:
	rm -fr *.bin *.o *.img *.elf
	rm -fr kernel/*.o drivers/*.o lib/*.o lib/*.a mm/*.o
	(cd boot;make clean)
