include ../vars.mak
INCLUDE_DIR=-I../include
all:	kernel.bin
kernel.bin: kernel_entry.o kernel.o ../lib/libbc.a
	ld -melf_i386 -o kernel.bin -Ttext 0x1000 $^ --oformat binary
kernel_entry.o:	kernel_entry.asm
	nasm -felf -o $@ $<
clean:
	rm *.o *.bin