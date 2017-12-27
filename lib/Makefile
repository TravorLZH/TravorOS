INCLUDE_DIR=-I../include
libio_SOURCES=basic_io.c
libio_OBJ=basic_io.o
libbc_SOURCES=$(wildcard libbc/*.c)
include ../vars.mak
all:	libio.a libbc.a
libbc.a:	$(libbc_SOURCES)
	make -C libbc
libio.a:	$(libio_OBJ)
	ar rc $@ $^
clean:
	rm -f *.a *.o libbc/*.a libbc/*.o