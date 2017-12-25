C_SOURCES=$(wildcard drivers/*.c kernel/*.c)
INCLUDE_DIR=-Iinclude
include vars.mak
LIBS=lib/libio.a lib/libbc.a
OBJ=${C_SOURCES:.c=.o}
.PHONY:	clean libs all run
all:	os.img
run:
	qemu-system-i386 -fda os.img
os.img:	boot/bootload.bin kernel/kernel.bin libs
	cat boot/bootload.bin kernel/kernel.bin > os.img
kernel/kernel.bin:	kernel/kernel_entry.o $(OBJ) $(LIBS)
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary
libs:
	make -C lib
%.a:
	make -C lib `basename $@`
%.o:	%.c
	gcc $(INCLUDE_DIR) -m32 -ffreestanding -c $< -o $@
%.o:	%.asm
	$(AS) $< -f elf -o $@
boot/bootload.bin:
	$(MAKE) -C boot
clean:
	rm -fr *.bin *.o *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o
	make -C lib clean