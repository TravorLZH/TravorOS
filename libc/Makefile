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

clean-dep:
	sed '/\#\#\# Dependencies/q' < Makefile > Makefile_temp
	cp Makefile_temp Makefile
	$(RM) -f Makefile_temp

clean:
	rm -rf *.o *.a

### Dependencies
