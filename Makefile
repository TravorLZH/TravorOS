include vars.mak

os.img:
	$(MAKE) -C lib
	$(MAKE)	-C boot
	$(MAKE) -C kernel
	cat boot/bootload.bin kernel/kernel.bin > os.img
clean:
	$(MAKE) clean -C boot
	$(MAKE) clean -C lib
	$(MAKE) clean -C kernel
	rm *.img