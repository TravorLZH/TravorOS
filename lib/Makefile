INCLUDE_DIR=-I../include
libio_SOURCES=basic_io.c
libio_OBJ=basic_io.o
libbc_SOURCES=string.c ctypes.c conv.c hex.c io.c ../drivers/screen.c \
random.c fibonacci.c printf.c
libbc_OBJ=${libbc_SOURCES:.c=.o}
include ../vars.mak
all:	libio.a libbc.a
libio.a:	$(libio_OBJ)
	@echo "Linking $<"
	@ar rc $@ $^
libbc.a:	$(libbc_OBJ)	
	@echo "Linking $<"
	ar rc $@ $^
clean:
	@echo Cleaning
	@rm -f *.a *.o
