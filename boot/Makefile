all:	boot.img
boot.img:	bootload.bin stage2.bin
	cat $^ > $@
%.bin:	%.asm general.inc
	yasm -fbin $< -o $@
clean:
	rm -f *.img *.bin
