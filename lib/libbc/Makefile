INCLUDE_DIR=-I../../include
SOURCES=$(wildcard *.c)
OBJ=${SOURCES:.c=.o}
include ../../vars.mak
all:	libbc.a
	cp libbc.a ../libbc.a
libbc.a:	$(OBJ)
	ar rc $@ $^