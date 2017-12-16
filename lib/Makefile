INCLUDE_DIR=-I../include
all:	libbc.a
include ../vars.mak
libbc.a:	api.o basic.o
	ar rc $@ $^
clean:
	rm *.a *.o