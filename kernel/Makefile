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

clean-dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	cp Makefile_temp Makefile
	$(RM) -f Makefile_temp

clean:
	rm -rf *.a *.o
### Dependencies
