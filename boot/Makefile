SOURCES=$(wildcard *.asm 32bit/*.asm)
include ../vars.mak
all:	bootload.bin
bootload.bin:	$(SOURCES)
	@echo "Assembling $^"
	@$(AS) -fbin bootload.asm -o $@
clean:
	@echo Cleaning
	@rm *.bin
