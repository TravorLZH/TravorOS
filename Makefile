C_SOURCES=$(wildcard drivers/*.c kernel/*.c)
INCLUDE_DIR=-Iinclude
OBJ=${C_SOURCES:.c=.o}
all:	os.img
os.img:	boot/bootload.bin kernel/kernel.bin
	cat boot/bootload.bin kernel/kernel.bin > os.img
kernel/kernel.bin:	kernel/kernel_entry.o $(OBJ)
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary
%.o:	%.c
	gcc $(INCLUDE_DIR) -m32 -ffreestanding -c $< -o $@
%.o:	%.asm
	nasm $< -f elf -o $@
%.bin:	%.asm
	nasm $< -f bin -o $@
clean:
	rm -fr *.bin *.o *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o