%.o:	%.c
	gcc -ffreestanding -m32 -c $< -o $@ $(INCLUDE_DIR)
