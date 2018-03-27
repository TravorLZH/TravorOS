include config.mk
C_SOURCES=$(wildcard kernel/*.c mm/*.c)
ASM_SOURCES=$(filter-out kernel/kernel_entry.asm kernel/grub_entry.asm,$(wildcard kernel/*.asm mm/*.asm))
INCLUDE_DIR=-Iinclude
kernel_LIBS=lib/libc.a
libc_SOURCES=$(wildcard lib/*.c lib/*.asm)
libc_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(libc_SOURCES)))
drivers_STUFF=$(addprefix drivers/,$(drivers_TARGETS))
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o} $(drivers_STUFF)

.PHONY:	clean all run debug dep $(drivers_STUFF) boot/boot.img
all:	floppy.img kernel.elf cdrom.iso
run:
	qemu-system-i386 -fda floppy.img -device isa-debug-exit,iobase=0xF4,iosize=0x04
debug:	all
	exec gdb -tui -x debug.gdb
boot/boot.img:
	(cd boot;$(MAKE) boot.img)
run-iso:
	qemu-system-i386 -cdrom cdrom.iso
cdrom.iso:	iso/boot/kernel.img
	@echo "Creating CD-ROM"
	@grub-mkrescue -o $@ iso/ 1>/dev/null 2>/dev/null
iso/boot/kernel.img:	kernel/grub_entry.o $(OBJ) $(kernel_LIBS)
	@echo "Linking multiboot kernel"
	@$(LD) -melf_i386 -o $@ -T link.ld $^
floppy.img: boot/boot.img kernel.bin
	@echo "Creating floppy disk"
	@cat boot/boot.img kernel.bin > floppy.img
kernel.bin:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	@echo "Linking kernel"
	@$(LD) -melf_i386 -o $@ -T link.ld $^ --oformat binary
kernel.elf:	kernel/kernel_entry.o $(OBJ) $(kernel_LIBS)
	@echo "Creating kernel symbol file"
	@$(LD) -melf_i386 -o $@ -T link.ld $^
$(drivers_STUFF):
	(cd drivers;$(MAKE) $(patsubst drivers/%.elf,%.elf,$@))
lib/libc.a:	$(libc_OBJ)
	ar rc $@ $^
dep:
	@$(MAKE) -C boot
	@$(MAKE) -C drivers
clean:
	$(RM) -fr *.bin *.o *.img *.elf
	$(RM) -fr kernel/*.o drivers/*.o lib/*.o lib/*.a mm/*.o
	$(RM) -fr iso/boot/kernel.img
	@$(MAKE) -C boot clean
	@$(MAKE) -C drivers clean
### Dependencies
mm/paging.o:	mm/paging.c include/kernel/memory.h include/stdio.h
mm/frame.o:	mm/frame.c include/kernel/memory.h include/kernel/utils.h \
	include/kernel/dbg.h
kernel/kernel.o:	kernel/kernel.c $(wildcard include/kernel/*.h) $(wildcard include/drivers/*.h)
kernel/dbg.o:	kernel/dbg.c include/kernel/dbg.h include/kernel/utils.h
