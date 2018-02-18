AS=yasm
CC=gcc
LD=ld

C_SOURCES=$(wildcard drivers/*.c kernel/*.c)
ASM_SOURCES=$(wildcard drivers/*.asm)
BOOT_SRC=$(wildcard boot/*.asm boot/32bit/*.asm)
INCLUDE_DIR=-Iinclude
kernel_LIBS=lib/libc.a
OBJ=${C_SOURCES:.c=.o drivers/interrupt.o}
libc_SOURCES=$(wildcard lib/*.c lib/*.asm)
libc_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(libc_SOURCES)));

%.o:	%.c
	@echo "Compiling $^"
	@${CC} -g -ffreestanding -nostdlib -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	@echo "Assembling $^"
	@${AS} -felf $< -o $@
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
	@$(LD) -melf_i386 -o $@ -e0x1000 -Ttext 0x1000 $^ --oformat binary
kernel.elf:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	@echo "Linking kernel symbol file"
	@$(LD) -melf_i386 -o $@ -emain -Ttext 0x1000 $^
drivers/interrupt.o:	drivers/interrupt.asm
boot/bootload.bin:	$(BOOT_SRC)
	@echo "Building bootloader"
	@$(AS) -fbin boot/bootload.asm -o $@
lib/libc.a:	$(libc_OBJ)	
	@echo "Linking $<"
	@ar rc $@ $^
clean:
	@echo "Cleaning"
	@rm -fr *.bin *.o *.img *.elf
	@rm -fr kernel/*.o kernel/*.bin boot/*.bin drivers/*.o lib/*.o lib/*.a
