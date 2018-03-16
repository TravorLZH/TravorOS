include	../config.mk
INCLUDE_DIR=-I../include
all:	$(drivers_TARGETS)
# Interrupt driver
int_SOURCES=$(wildcard int/*.c int/*.asm)
int_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(int_SOURCES)))
int.elf:	$(int_OBJ)
# Disk drivers
disk_SOURCES=$(wildcard disk/*.c)
disk_OBJ=$(disk_SOURCES:.c=.o)
disk.elf:	$(disk_OBJ)
# Time and clock drivers
time_SOURCES=$(wildcard time/*.c)
time_OBJ=$(time_SOURCES:.c=.o)
time.elf:	$(time_OBJ)
# Standard input and output
stdio_SOURCES=$(wildcard stdio/*.c)
stdio_OBJ=$(stdio_SOURCES:.c=.o)
stdio.elf:	$(stdio_OBJ)
# Global Descriptor Table
gdt_SOURCES=$(wildcard gdt/*.c gdt/*.asm)
gdt_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(gdt_SOURCES)))
gdt.elf:	$(gdt_OBJ)
# All objects
drivers_OBJ=$(time_OBJ) $(stdio_OBJ) $(disk_OBJ) $(int_OBJ) $(gdt_OBJ)
### Dependencies
int/idt.o:	int/idt.c ../include/cpu/idt.h
int/isr.o:	int/isr.c ../include/cpu/idt.h ../include/cpu/isr.h \
	../include/stdio.h ../include/asm/ioports.h
# All objects
%.elf:
	$(LD) -melf_i386 -r -o $@ $^
clean:
	rm -f $(drivers_OBJ)
	rm -f $(drivers_TARGETS)
