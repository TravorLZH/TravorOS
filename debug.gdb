add-symbol-file kernel.elf 0x1000
break kernel/kernel.c:main
target remote | qemu-system-i386 -S -gdb stdio -fda os.img
# vim: set syntax=gdb:
