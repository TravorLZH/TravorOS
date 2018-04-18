include ../config.mk
all:	boot.img
boot.img:	bootload.bin stage2.bin
	$(call green,"GEN $@")
	@cat $^ > $@
%.bin:	%.asm general.inc
	$(call white,"AS $@")
	@${AS} -fbin $< -o $@
clean:
	rm -f *.img *.bin
