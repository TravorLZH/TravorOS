INCLUDE_DIR=-I../include
libio_SOURCES=basic_io.c
libio_OBJ=basic_io.o
libbc_SOURCES=string.c ctypes.c conv.c hex.c io.c
libbc_OBJ=${libbc_SOURCES:.c=.o}
include ../vars.mak
all:	libio.a libbc.a
libio.a:	$(libio_OBJ)
	ar rc $@ $^
libbc.a:	$(libbc_OBJ)	
	ar rc $@ $^
clean:
	rm -f *.a *.o
