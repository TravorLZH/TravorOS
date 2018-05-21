AS=yasm
CC=gcc
LD=ld
drivers_TARGETS=cpu.elf time.elf tty.elf
CPPFLAGS=-ffreestanding -nostdlib
CFLAGS=-Wno-implicit-function-declaration -Wno-packed-bitfield-compat -g -m32
QEMU_FLAGS=-device isa-debug-exit,iobase=0xF4,iosize=0x04
ifndef	VERBOSE
MAKEFLAGS += --no-print-directory
endif
define yellow
	@echo -n "\033[1;33m"
	@echo -n $1
	@echo "\033[0m"
endef
define green
	@echo -n "\033[1;32m"
	@echo -n $1
	@echo "\033[0m"
endef
define white
	@echo -n "\033[1;37m"
	@echo -n $1
	@echo "\033[0m"
endef
%.o:	%.c
	$(call white,"CC $@")
	@${CC} $(CFLAGS) $(CPPFLAGS) -c $< -o $@
%.o:	%.asm
	$(call white,"AS" "$@")
	@${AS} -felf $< -o $@
