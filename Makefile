include config.mk
C_SOURCES=$(wildcard init/*.c mm/*.c)
ASM_SOURCES=$(filter-out init/kernel_entry.asm init/grub_entry.asm,$(wildcard mm/*.asm init/*.asm))
CPPFLAGS+=-Iinclude -Iliballoc
kernel_LIBS=kernel/libkernel.a libc/libc.a liballoc/liballoc.a
drivers_STUFF=$(addprefix drivers/,$(drivers_TARGETS))
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}
.PHONY:	clean all run debug dep fo$(RM)at drivers $(kernel_LIBS)
all:	drivers floppy.img kernel.elf cdrom.iso

config:
	sh tools/config.sh

format:
	sh tools/format_function.sh
run:
	exec qemu-system-i386 -fda floppy.img $(QEMU_FLAGS)
curses:
	exec qemu-system-i386 -curses -fda floppy.img $(QEMU_FLAGS)
debug:
	exec gdb -tui -x debug.gdb
run-iso:
	exec qemu-system-i386 -cdrom cdrom.iso $(QEMU_FLAGS)
curses-iso:
	exec qemu-system-i386 -curses -cdrom cdrom.iso $(QEMU_FLAGS)

cdrom.iso:	iso/boot/kernel.img
	$(call green,"GEN $@")
	@grub-mkrescue -o $@ iso/

iso/boot/kernel.img:	init/grub_entry.o $(OBJ) $(drivers_STUFF) $(kernel_LIBS)
	$(call green,"GEN $@")
	@$(LD) -melf_i386 -o $@ -T link.ld $^

floppy.img: boot/boot.img kernel.bin
	$(call green,"GEN $@")
	@dd status=noxfer if=/dev/zero of=floppy.img bs=512 count=2880
	@dd status=noxfer conv=notrunc if=boot/boot.img of=floppy.img
	@dd status=noxfer if=kernel.bin of=floppy.img bs=1024 seek=1

kernel.bin:	init/kernel_entry.o $(OBJ) $(drivers_STUFF) $(kernel_LIBS)
	$(call yellow,"LINK $@")
	@$(LD) -melf_i386 -o $@ -T link.ld $^ --oformat binary

kernel.elf:	init/kernel_entry.o $(OBJ) $(drivers_STUFF) $(kernel_LIBS)
	$(call green,"GEN $@")
	@$(LD) -melf_i386 -o $@ -T link.ld $^

# Subdirectory targets
drivers:
	$(call yellow,"SUBDIR drivers")
	@$(MAKE) -C drivers

boot/boot.img:
	@$(call yellow,"SUBDIR boot")
	@$(MAKE) -C boot boot.img

liballoc/liballoc.a:
	@$(call yellow,"SUBDIR liballoc")
	@$(MAKE) -C liballoc liballoc.a

libc/libc.a:
	@$(call yellow,"SUBDIR libc")
	@$(MAKE) -C libc libc.a

kernel/libkernel.a:
	@$(call yellow,"SUBDIR kernel")
	@$(MAKE) -C kernel libkernel.a

# Generate dependencies
dep:	config
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	(for i in mm/*.c;do echo -n mm/;$(CPP) $(CPPFLAGS) -M $$i;done) >> Makefile_temp
	(for i in init/*.c;do echo -n init/;$(CPP) $(CPPFLAGS) -M $$i;done) >> Makefile_temp
	cp Makefile_temp Makefile
	$(RM) Makefile_temp
	@$(MAKE) -C drivers dep
	@$(MAKE) -C libc dep
	@$(MAKE) -C kernel dep

# Clean objects
clean:
	$(RM) -rf *.bin *.o *.img *.elf *.iso boot/*.bin boot/*.img
	$(RM) -rf init/*.o mm/*.o
	$(RM) -rf iso/boot/kernel.img
	@$(MAKE) -C boot clean
	@$(MAKE) -C drivers clean
	@$(MAKE) -C liballoc clean
	@$(MAKE) -C libc clean
	@$(MAKE) -C kernel clean

### Dependencies
mm/frame.o: mm/frame.c include/kernel/memory.h include/def.h \
 include/sys/types.h include/errno.h include/kernel/dbg.h \
 include/kernel/utils.h include/kernel/bsod.h include/cpu/isr.h \
 include/bitset32.h
mm/heap.o: mm/heap.c include/kernel/memory.h include/def.h \
 include/sys/types.h include/errno.h include/kernel/dbg.h \
 include/kernel/utils.h
mm/paging.o: mm/paging.c include/kernel/memory.h include/def.h \
 include/sys/types.h include/errno.h include/bitset32.h \
 include/kernel/utils.h include/kernel/dbg.h include/kernel/bsod.h \
 include/cpu/isr.h include/asm/string.h include/drivers/screen.h \
 include/stdio.h /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h
init/main.o: init/main.c include/stdio.h include/def.h include/sys/types.h \
 include/errno.h /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h \
 include/config.h include/drivers/screen.h include/drivers/keyboard.h \
 include/drivers/rtc.h include/kernel/memory.h include/kernel/utils.h \
 include/kernel/dbg.h include/kernel/multiboot.h include/kernel/syscall.h \
 include/cpu/gdt.h include/cpu/isr.h include/cpu/timer.h \
 include/asm/interrupt.h include/asm/ioports.h
init/shell.o: init/shell.c include/config.h include/kernel/utils.h \
 include/kernel/dbg.h include/asm/string.h include/def.h \
 include/sys/types.h include/errno.h include/asm/ioports.h \
 include/cpu/timer.h include/cpu/cpuid.h include/drivers/rtc.h \
 liballoc/liballoc.h
