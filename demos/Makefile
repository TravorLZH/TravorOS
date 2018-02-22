SOURCES=$(wildcard *.asm)
TARGETS=${SOURCES:.asm=.bin}
all:	$(TARGETS)
	@echo "DONE"
%.bin:	%.asm
	@echo "Compiling $^"
	@yasm -fbin -o $@ $^
.PHONY:	clean
clean:
	@echo "Cleaning binaries"
	@rm -rf *.bin
