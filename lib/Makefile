INCLUDE_DIR=-I../include
C_SOURCES=$(wildcard *.c)
ASM_SOURCES=$(wildcard *.asm)
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}
all:	libbc.a
include ../vars.mak
libbc.a:	$(OBJ)
	ar rc $@ $^
clean:
	rm *.a *.o