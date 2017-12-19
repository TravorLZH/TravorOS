include ../vars.mak
INCLUDE_DIR=-I../include
C_SOURCES=$(wildcard *.c)
ASM_SOURCES=$(wildcard *.asm)
OBJ=${C_SOURCES:.c=.o} ${ASM_SOURCES:.asm=.o}
LIBS=../lib/libbc.a
HEADERS=$(wildcard ../include/*.h)
all:	kernel.bin
kernel.bin: $(OBJ) $(LIBS) $(HEADERS)
	ld -melf_i386 -o kernel.bin -Ttext 0x1000 $(OBJ) $(LIBS) --oformat binary
clean:
	rm *.o *.bin