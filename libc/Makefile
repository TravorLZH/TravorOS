include ../config.mk
CPPFLAGS+=-I../include -I../liballoc

SOURCES=$(wildcard *.c)
OBJ=$(SOURCES:.c=.o)

all:	libc.a

libc.a:	$(OBJ)
	$(call yellow,"LINK $@")
	@ar rc $@ $^

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	(for i in *.c;do $(CPP) $(CPPFLAGS) -M $$i;done) >> Makefile_temp
	cp Makefile_temp Makefile
	rm -f Makefile_temp

clean:
	rm -rf *.o *.a

### Dependencies
conv.o: conv.c ../include/misc.h ../include/sys/types.h
ctypes.o: ctypes.c ../include/def.h ../include/sys/types.h \
 ../include/errno.h ../include/ctypes.h
fibonacci.o: fibonacci.c ../include/fibonacci.h ../include/sys/types.h
hex.o: hex.c ../include/misc.h ../include/sys/types.h
iowrap.o: iowrap.c ../include/stdio.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h \
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h ../include/string.h \
 ../include/kernel/syscall.h ../include/drivers/screen.h
printf.o: printf.c ../include/kernel/utils.h ../include/kernel/dbg.h \
 /usr/lib/gcc/x86_64-linux-gnu/4.8/include/stdarg.h ../include/string.h \
 ../include/def.h ../include/sys/types.h ../include/errno.h \
 ../include/stdio.h
random.o: random.c ../include/random.h ../include/fibonacci.h \
 ../include/sys/types.h
string.o: string.c ../include/string.h ../include/def.h \
 ../include/sys/types.h ../include/errno.h
