include ../config.mk
CPPFLAGS+=-I../include -I../liballoc

C_SOURCES=$(wildcard *.c)
ASM_SOURCES=$(wildcard *.asm)
OBJ=$(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)

all:	libkernel.a

libkernel.a:	$(OBJ)
	$(call yellow,"LINK libkernel.a")
	@ar rc $@ $^

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	(for i in *.c;do $(CPP) $(CPPFLAGS) -M $$i;done) >> Makefile_temp
	cp Makefile_temp Makefile
	rm -f Makefile_temp

clean:
	rm -rf *.a *.o
### Dependencies
bitset32.o: bitset32.c ../include/string.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h ../include/bitset32.h
bsod.o: bsod.c ../include/kernel/bsod.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h ../include/cpu/isr.h \
 ../include/kernel/utils.h ../include/kernel/dbg.h \
 ../include/drivers/screen.h
dbg.o: dbg.c ../include/kernel/dbg.h ../include/kernel/utils.h \
 ../include/stdio.h ../include/def.h ../include/sys/types.h \
 ../include/errno.h /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h
utils.o: utils.c /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h \
 ../include/def.h ../include/sys/types.h ../include/errno.h \
 ../include/kernel/utils.h ../include/kernel/dbg.h \
 ../include/drivers/screen.h
