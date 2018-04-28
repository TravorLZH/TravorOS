include	../config.mk
INCLUDE_DIR=-I../include
all:	$(drivers_TARGETS)
# GDT and IDT drivers
cpu_SOURCES=$(wildcard cpu/*.c cpu/*.asm)
cpu_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(cpu_SOURCES)))
cpu.elf:	$(cpu_OBJ)
# Time and clock drivers
time_SOURCES=$(wildcard time/*.c)
time_OBJ=$(time_SOURCES:.c=.o)
time.elf:	$(time_OBJ)
# Standard input and output
tty_SOURCES=$(wildcard tty/*.c)
tty_OBJ=$(tty_SOURCES:.c=.o)
tty.elf:	$(tty_OBJ)
# All objects
drivers_OBJ=$(time_OBJ) $(tty_OBJ) $(cpu_OBJ)
%.elf:
	$(call green,"GEN $@")
	@$(LD) -melf_i386 -r -o $@ $^
dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	(for x in $(drivers_TARGETS:.elf=/);do \
	(for i in $${x}*.c;do \
	echo -n $$x;$(CPP) $(CPPFLAGS) -I../include -M $$i;done) >> Makefile_temp;done)
	cp Makefile_temp Makefile
	rm Makefile_temp
clean:
	(for x in $(drivers_TARGETS:.elf=/);do \
	rm -rf $${x}*.o $${x}*.c.asm;done)
	rm -rf *.elf
### Dependencies
cpu/gdt.o: cpu/gdt.c ../include/cpu/gdt.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h
cpu/idt.o: cpu/idt.c ../include/cpu/idt.h ../include/sys/types.h
cpu/isr.o: cpu/isr.c ../include/cpu/idt.h ../include/sys/types.h \
 ../include/cpu/isr.h ../include/stdio.h ../include/def.h \
 ../include/errno.h /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h \
 ../include/asm/ioports.h
time/rtc.o: time/rtc.c ../include/kernel/cmos.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h ../include/asm/ioports.h \
 ../include/drivers/rtc.h
time/timer.o: time/timer.c ../include/cpu/timer.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h ../include/cpu/isr.h \
 ../include/kernel/utils.h ../include/kernel/dbg.h \
 ../include/asm/ioports.h ../include/drivers/screen.h
tty/keyboard.o: tty/keyboard.c ../include/stdio.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h \
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h \
 ../include/asm/string.h ../include/asm/ioports.h ../include/cpu/isr.h \
 ../include/drivers/keyboard.h ../include/kernel/utils.h \
 ../include/kernel/dbg.h
tty/screen.o: tty/screen.c ../include/asm/ioports.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h ../include/drivers/screen.h
