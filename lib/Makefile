INCLUDE_DIR=-I../include
#libbc_SOURCES=basic.c
libbc_OBJ=${libbc_SOURCES:.c=.o}
libio_SOURCES=basic_io.c
libio_OBJ=basic_io.o
include ../vars.mak
all:	libio.a
#libbc.a:	$(libbc_OBJ)
#	ar rc $@ $^
libio.a:	$(libio_OBJ)
	ar rc $@ $^
clean:
	rm -f *.a *.o