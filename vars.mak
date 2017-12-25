AS=yasm
%.o:	%.c
	gcc -ffreestanding -m32 -c $< -o $@ $(INCLUDE_DIR)
%.o:	%.asm
	$(AS) -felf $< -o $@
