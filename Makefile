C_SOURCES=$(wildcard drivers/*.c kernel/*.c)
INCLUDE_DIR=-Iinclude
LIBS=lib/libio.a
OBJ=${C_SOURCES:.c=.o}
all:	os.img libs
run:	os.img
	qemu-system-i386 -fda os.img
os.img:	boot/bootload.bin kernel/kernel.bin
	cat boot/bootload.bin kernel/kernel.bin > os.img
kernel/kernel.bin:	kernel/kernel_entry.o $(OBJ) $(LIBS)
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary
libs:
	make -C lib
%.o:	%.c
	gcc $(INCLUDE_DIR) -m32 -ffreestanding -c $< -o $@
%.o:	%.asm
	nasm $< -f elf -o $@
boot/bootload.bin:
	make -C boot
clean:
	rm -fr *.bin *.o *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o