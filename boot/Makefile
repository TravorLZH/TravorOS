SOURCES=$(wildcard *.asm 32bit/*.asm)
include ../vars.mak
all:	bootload.bin
bootload.bin:	$(SOURCES)
	$(AS) -fbin bootload.asm -o $@
clean:
	rm *.bin
