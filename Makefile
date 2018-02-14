C_SOURCES=$(wildcard drivers/*.c kernel/*.c)
ASM_SOURCES=$(wildcard drivers/*.asm)
BOOT_SRC=$(wildcard boot/*.asm)
LIB_SRC=$(wildcard lib/*.c)
LIB_OBJ=${LIB_SRC:.c=.o}
INCLUDE_DIR=-Iinclude
include vars.mak
kernel_LIBS=lib/libio.a lib/libbc.a
OBJ=${C_SOURCES:.c=.o drivers/interrupt.o}
.PHONY:	clean all run debug
all:	os.img kernel.elf
run:	os.img
	@qemu-system-i386 -fda os.img
debug:	os.img kernel.elf
	@exec gdb -tui -x debug.gdb
os.img:	boot/bootload.bin kernel/kernel.bin $(kernel_LIBS)
	@echo "Creating OS Image"
	@cat boot/bootload.bin kernel/kernel.bin > os.img
kernel/kernel.bin:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	@echo "Linking kernel.bin"
	@ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary
kernel.elf:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	@echo "Linking kernel symbol file"
	@ld -melf_i386 -o $@ -Ttext 0x1000 $^
drivers/interrupt.o:	drivers/interrupt.asm
$(kernel_LIBS):	$(LIB_OBJ)
	@echo "Building libraries"
	@$(MAKE) -C lib
boot/bootload.bin:	$(BOOT_SRC)
	@echo "Building bootloader"
	@$(MAKE) -C boot
clean:
	@echo "Cleaning"
	@rm -fr *.bin *.o *.img *.elf
	@rm -fr kernel/*.o boot/*.bin drivers/*.o
	@make -C lib clean
