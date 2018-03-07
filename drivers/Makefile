include	../config.mk
INCLUDE_DIR=-I../include
# Interrupt driver
int_SOURCES=$(wildcard int/*.c int/*.asm)
int_OBJ=$(patsubst %.c,%.o,$(patsubst %.asm,%.o,$(int_SOURCES)))
# Disk drivers
disk_SOURCES=$(wildcard disk/*.c)
disk_OBJ=$(disk_SOURCES:.c=.o)
# Time and clock drivers
time_SOURCES=$(wildcard time/*.c)
time_OBJ=$(time_SOURCES:.c=.o)
# Standard input and output
stdio_SOURCES=$(wildcard stdio/*.c)
stdio_OBJ=$(stdio_SOURCES:.c=.o)
# All objects
drivers_OBJ=$(int_OBJ) $(disk_OBJ) $(time_OBJ) $(stdio_OBJ)

all:	$(drivers_OBJ)
clean:
	rm -f $(drivers_OBJ)
