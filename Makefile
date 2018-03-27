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
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	(for i in kernel/*.c;do echo -n kernel/;$(CPP) $(CPPFLAGS) -Iinclude -M $$i;done) >> Makefile_temp
	(for i in mm/*.c;do echo -n mm/;$(CPP) $(CPPFLAGS) -Iinclude -M $$i;done) >> Makefile_temp
	cp Makefile_temp Makefile
	rm Makefile_temp
	make -C drivers dep
clean:
	$(RM) -fr *.bin *.o *.img *.elf
	$(RM) -fr kernel/*.o drivers/*.o lib/*.o lib/*.a mm/*.o
	$(RM) -fr iso/boot/kernel.img
	@$(MAKE) -C boot clean
	@$(MAKE) -C drivers clean
### Dependencies
kernel/bitset32.o: kernel/bitset32.c include/string.h include/def.h \
 include/types.h include/errno.h include/bitset32.h
kernel/bsod.o: kernel/bsod.c include/kernel/bsod.h include/def.h include/types.h \
 include/errno.h include/kernel/utils.h include/kernel/dbg.h \
 include/drivers/screen.h
kernel/dbg.o: kernel/dbg.c include/kernel/dbg.h include/kernel/utils.h \
 include/stdio.h include/def.h include/types.h include/errno.h \
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h include/io.h \
 include/drivers/screen.h
kernel/kernel.o: kernel/kernel.c include/config.h include/stdio.h include/def.h \
 include/types.h include/errno.h \
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h include/io.h \
 include/drivers/screen.h include/kernel/memory.h include/kernel/utils.h \
 include/kernel/dbg.h include/kernel/multiboot.h include/cpu/gdt.h \
 include/cpu/isr.h include/cpu/timer.h include/asm/interrupt.h \
 include/asm/shutdown.h
kernel/utils.o: kernel/utils.c \
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h include/def.h \
 include/types.h include/errno.h include/kernel/utils.h \
 include/kernel/dbg.h include/drivers/screen.h
mm/frame.o: mm/frame.c include/kernel/memory.h include/def.h include/types.h \
 include/errno.h include/kernel/dbg.h include/kernel/utils.h \
 include/kernel/bsod.h include/bitset32.h
mm/heap.o: mm/heap.c include/kernel/memory.h include/def.h include/types.h \
 include/errno.h include/kernel/dbg.h include/kernel/utils.h
mm/paging.o: mm/paging.c include/kernel/memory.h include/def.h \
 include/types.h include/errno.h include/bitset32.h \
 include/kernel/utils.h include/kernel/dbg.h include/kernel/bsod.h \
 include/asm/shutdown.h include/drivers/screen.h include/cpu/isr.h \
 include/stdio.h /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h \
 include/io.h
