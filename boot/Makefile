include ../config.mk
all:	boot.img
boot.img:	bootload.bin stage2.bin
	@echo "GEN" "$@"
	@cat $^ > $@
%.bin:	%.asm general.inc
	@echo "AS" "$@"
	@${AS} -fbin $< -o $@
clean:
	rm -f *.img *.bin
