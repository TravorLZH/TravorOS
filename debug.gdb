add-symbol-file kernel.elf 0x100000
break init/main.c:kernel_main
set disassembly-flavor intel
target remote | qemu-system-i386 -S -gdb stdio -fda floppy.img -device isa-debug-exit,iobase=0xF4,iosize=0x04
continue
