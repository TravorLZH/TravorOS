# Please see LICENSE for licensing information.


# --------- FLAGS AND VARIABLES --------------------

CC=i386-elf-gcc
AR=i386-elf-ar
CFLAGS=-m32 -O2 -nostdlib -nodefaultlibs -fno-builtin -Wall -Wno-packed-bitfield-compat
HEADERPATH=-I./ -I../include



# ---------  GENERIC MAKE RULES --------------------

all: 
	@echo "Makefile for the liballoc library."
	@echo "Please see LICENSE for licensing information."
	@echo 
	@echo "Output should be: liballoc.a "
	@echo "                  liballoc.so"
	@echo 
	@echo "Usage: make [ compile | clean | <platform> ] "
	@echo 
	@echo "Currently supported platforms:"
	@echo 
	@echo "      linux"
	@echo "      linux_debug"
	@echo
	@echo
	@echo "Please see the README for example usage"


clean:
	rm -f ./*.o
	rm -f ./*.a
	rm -f ./*.so

compile:
	$(CC) $(HEADERPATH) $(CFLAGS) -static -c liballoc.c
	$(AR) -rcv liballoc.a  *.o
	$(CC) $(HEADERPATH) $(CFLAGS) -shared liballoc.c -o liballoc.so


linux:
	gcc $(HEADERPATH) $(CFLAGS) -static -c liballoc.c linux.c
	ar -rcv liballoc.a  *.o
	gcc $(HEADERPATH) $(CFLAGS) -shared liballoc.c linux.c -o liballoc.so


linux_debug:
	gcc -DDEBUG $(HEADERPATH) $(CFLAGS) -static -c liballoc.c linux.c
	ar -rcv liballoc.a  *.o
	gcc -DDEBUG $(HEADERPATH) $(CFLAGS) -shared liballoc.c linux.c -o liballoc.so
liballoc.a:
	$(CC) $(HEADERPATH) -I../include $(CFLAGS) -static -c liballoc.c travoros.c
	$(AR) -rcv $@ liballoc.o travoros.o
