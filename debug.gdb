add-symbol-file kernel.elf 0x1000
#break drivers/isr.c:26
target remote | qemu-system-i386 -S -gdb stdio -fda os.img
