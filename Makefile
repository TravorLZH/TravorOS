include config.mk
C_SOURCES=$(wildcard init/*.c mm/*.c fs/*.c)
ASM_SOURCES=$(filter-out init/kernel_entry.asm init/grub_entry.asm,$(wildcard mm/*.asm init/*.asm))
CPPFLAGS+=-Iinclude -Iliballoc
kernel_LIBS=kernel/libkernel.a libc/libc.a liballoc/liballoc.a
drivers_STUFF=$(addprefix drivers/,$(drivers_TARGETS))
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}
.PHONY:	clean all run debug dep format drivers $(kernel_LIBS) boot/boot.img
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

cdrom.iso:	iso/boot/kernel.img iso/boot/initrd.img
	$(call green,"GEN $@")
	@grub-mkrescue -o $@ iso/

iso/boot/kernel.img:	init/grub_entry.o $(OBJ) $(drivers_STUFF) $(kernel_LIBS)
	$(call green,"GEN $@")
	@$(LD) -melf_i386 -o $@ -T link.ld $^

iso/boot/initrd.img:	tools/make_initrd
	tools/make_initrd test.txt test.txt

tools/make_initrd:	tools/make_initrd.c	# This won't need cross-compiler
	gcc -o $@ $^

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

clean-dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	cp Makefile_temp Makefile
	$(RM) -f Makefile_temp
	$(MAKE) -C drivers clean-dep
	$(MAKE) -C libc clean-dep
	$(MAKE) -C kernel clean-dep
# Clean objects
clean:	clean-dep
	$(RM) -rf *.bin *.o *.img *.elf *.iso boot/*.bin boot/*.img
	$(RM) -rf init/*.o mm/*.o
	$(RM) -rf iso/boot/*.img
	@$(MAKE) -C boot clean
	@$(MAKE) -C drivers clean
	@$(MAKE) -C liballoc clean
	@$(MAKE) -C libc clean
	@$(MAKE) -C kernel clean

### Dependencies
