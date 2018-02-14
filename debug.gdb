add-symbol-file kernel.elf 0x1000
break kernel/kernel.c:main
set disassembly-flavor intel
target remote | qemu-system-i386 -S -gdb stdio -fda os.img
continue
