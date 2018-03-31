include	../config.mk
INCLUDE_DIR=-I../include
all:	$(drivers_TARGETS)
# Interrupt driver
int_SOURCES=$(wildcard int/*.c int/*.asm)
int_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(int_SOURCES)))
int.elf:	$(int_OBJ)
# Time and clock drivers
time_SOURCES=$(wildcard time/*.c)
time_OBJ=$(time_SOURCES:.c=.o)
time.elf:	$(time_OBJ)
# Standard input and output
tty_SOURCES=$(wildcard tty/*.c)
tty_OBJ=$(tty_SOURCES:.c=.o)
tty.elf:	$(tty_OBJ)
# Global Descriptor Table
gdt_SOURCES=$(wildcard gdt/*.c gdt/*.asm)
gdt_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(gdt_SOURCES)))
gdt.elf:	$(gdt_OBJ)
# All objects
drivers_OBJ=$(time_OBJ) $(tty_OBJ) $(int_OBJ) $(gdt_OBJ)
%.elf:
	$(LD) -melf_i386 -r -o $@ $^
dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	(for x in $(drivers_TARGETS:.elf=/);do \
	(for i in $${x}*.c;do \
	echo -n $$x;$(CPP) $(CPPFLAGS) -I../include -M $$i;done) >> Makefile_temp;done)
	cp Makefile_temp Makefile
	rm Makefile_temp
clean:
	(for x in $(drivers_TARGETS:.elf=/);do \
	rm -rf $${x}*.o;done)
	rm -rf *.elf
### Dependencies
int/idt.o: int/idt.c ../include/cpu/idt.h ../include/types.h
int/isr.o: int/isr.c ../include/cpu/idt.h ../include/types.h \
 ../include/cpu/isr.h ../include/stdio.h ../include/def.h \
 ../include/errno.h /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h \
 ../include/io.h ../include/drivers/screen.h ../include/asm/ioports.h
time/timer.o: time/timer.c ../include/cpu/timer.h ../include/def.h \
 ../include/types.h ../include/errno.h ../include/cpu/isr.h \
 ../include/kernel/utils.h ../include/kernel/dbg.h \
 ../include/asm/ioports.h ../include/drivers/screen.h
tty/kbd.o: tty/kbd.c ../include/drivers/kbd.h ../include/drivers/screen.h \
 ../include/def.h ../include/types.h ../include/errno.h \
 ../include/asm/ioports.h ../include/kernel/utils.h \
 ../include/kernel/dbg.h ../include/ctypes.h ../include/cpu/isr.h
tty/screen.o: tty/screen.c ../include/asm/ioports.h ../include/def.h \
 ../include/types.h ../include/errno.h ../include/drivers/screen.h
gdt/gdt.o: gdt/gdt.c ../include/cpu/gdt.h ../include/def.h ../include/types.h \
 ../include/errno.h
