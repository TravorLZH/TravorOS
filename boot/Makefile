SOURCES=$(wildcard *.asm 32bit/*.asm)
all:	bootload.bin
bootload.bin:	$(SOURCES)
	nasm -fbin bootload.asm -o $@
clean:
	rm *.bin