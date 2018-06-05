include	../config.mk
INCLUDE_DIR=-I../include -I../liballoc
CPPFLAGS+=$(INCLUDE_DIR)
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
# Block device
block_dev_SOURCES=$(wildcard block_dev/*.c)
block_dev_OBJ=$(block_dev_SOURCES:.c=.o)
block_dev.elf:	$(block_dev_OBJ)
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

clean-dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	cp Makefile_temp Makefile
	$(RM) -f Makefile_temp

clean:
	(for x in $(drivers_TARGETS:.elf=/);do \
	rm -rf $${x}*.o $${x}*.c.asm;done)
	rm -rf *.elf
### Dependencies
