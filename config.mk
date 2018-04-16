AS=yasm
CC=gcc
LD=ld
drivers_TARGETS=int.elf time.elf tty.elf gdt.elf
CPPFLAGS=-ffreestanding -nostdlib
CFLAGS=-Wno-implicit-function-declaration -Wno-packed-bitfield-compat -g -m32
ifndef	VERBOSE
MAKEFLAGS += --no-print-directory
endif
%.o:	%.c
	@echo "CC" "$@"
	@${CC} $(CFLAGS) $(CPPFLAGS) $(INCLUDE_DIR) -c $< -o $@
ifdef	GEN_ASM 
	@echo "GEN" "$<.dsasm"
	@exec objconv -fnasm $@ $<.dsasm 1>/dev/null 2>/dev/null
endif
%.o:	%.asm
	@echo "AS" "$@"
	@${AS} -felf $< -o $@
