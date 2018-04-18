AS=yasm
CC=gcc
LD=ld
drivers_TARGETS=cpu.elf time.elf tty.elf
CPPFLAGS=-ffreestanding -nostdlib
CFLAGS=-Wno-implicit-function-declaration -Wno-packed-bitfield-compat -g -m32
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
	@${CC} $(CFLAGS) $(CPPFLAGS) $(INCLUDE_DIR) -c $< -o $@
ifdef	GEN_ASM 
	$(call green,"GEN $<.dsasm")
	@exec objconv -fnasm $@ $<.dsasm 1>/dev/null 2>/dev/null
endif
%.o:	%.asm
	$(call white,"AS" "$@")
	@${AS} -felf $< -o $@
