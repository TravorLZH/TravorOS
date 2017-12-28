C_SOURCES=$(wildcard drivers/*.c kernel/*.c)
BOOT_SRC=$(wildcard boot/*.asm)
LIB_SRC=$(wildcard lib/*.c)
LIB_OBJ=${LIB_SRC:.c=.o}
INCLUDE_DIR=-Iinclude
include vars.mak
kernel_LIBS=lib/libio.a lib/libbc.a
OBJ=${C_SOURCES:.c=.o}
.PHONY:	clean all run
all:	os.img
run:
	qemu-system-i386 -fda os.img
os.img:	boot/bootload.bin kernel/kernel.bin $(kernel_LIBS)
	cat boot/bootload.bin kernel/kernel.bin > os.img
kernel/kernel.bin:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary
$(kernel_LIBS):	$(LIB_OBJ)
	$(MAKE) -C lib
boot/bootload.bin:	$(BOOT_SRC)
	$(MAKE) -C boot
clean:
	rm -fr *.bin *.o *.img
	rm -fr kernel/*.o boot/*.bin drivers/*.o
	make -C lib clean