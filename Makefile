include config.mk
C_SOURCES=$(wildcard kernel/*.c mm/*.c)
ASM_SOURCES=$(filter-out kernel/kernel_entry.asm kernel/grub_entry.asm,$(wildcard kernel/*.asm mm/*.asm))
INCLUDE_DIR=-Iinclude
kernel_LIBS=lib/libc.a
libc_SOURCES=$(wildcard lib/*.c lib/*.asm)
libc_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(libc_SOURCES)))
drivers_STUFF=$(addprefix drivers/,$(drivers_TARGETS))
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o} $(drivers_STUFF)

.PHONY:	clean all run debug dep
all:	os.img kernel.elf os.iso
run:
	qemu-system-i386 -fda os.img -device isa-debug-exit,iobase=0xF4,iosize=0x04
debug:	all
	exec gdb -tui -x debug.gdb
boot/boot.img:
	make -C boot boot.img
run-iso:
	qemu-system-i386 -cdrom os.iso
os.iso:	dep iso/boot/kernel.img
	grub-mkrescue -o $@ iso/ 1>/dev/null
iso/boot/kernel.img:	kernel/grub_entry.o $(OBJ) $(kernel_LIBS)
	$(LD) -melf_i386 -o $@ -T link.ld $^
os.img: boot/boot.img kernel.bin
	cat boot/boot.img kernel.bin > os.img
kernel.bin:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	$(LD) -melf_i386 -o $@ -T link.ld $^ --oformat binary
kernel.elf:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	$(LD) -melf_i386 -o $@ -T link.ld $^
lib/libc.a:	$(libc_OBJ)
	ar rc $@ $^
dep:
	@$(MAKE) -C boot
	@$(MAKE) -C drivers
clean:
	$(RM) -fr *.bin *.o *.img *.elf
	$(RM) -fr kernel/*.o drivers/*.o lib/*.o lib/*.a mm/*.o
	@$(MAKE) -C boot clean
	@$(MAKE) -C drivers clean
### Dependencies
mm/paging.o:	mm/paging.c mm/paging.h include/kernel/memory.h include/stdio.h
mm/frame.o:	mm/frame.c mm/paging.h include/kernel/memory.h include/kernel/utils.h
kernel/kernel.o:	kernel/kernel.c $(wildcard include/kernel/*.h)
kernel/dbg.o:	kernel/dbg.c include/kernel/dbg.h include/kernel/utils.h
