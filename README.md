# TravorOS - Developing with Simplification

This is the first [Operating System](https://en.wikipedia.org/wiki/Operating_System "Operating System Definition") I created. It's written in two languages: C language and Assembly.

This project has been activated since [December 15, 2017](https://github.com/TravorLZH/TravorOS/blob/master/ChangeLog.md#01-r0-2017-12-15)

### Bootloader

This OS uses a bootloader that switches from **16-bit real mode** to **32-bit protected mode**. It loads kernel code into memory before it entered 32-bit protected mode.

### Kernel

It's written in C. It simply calls other C standard functions that I implemented myself in [lib](https://github.com/TravorLZH/TravorOS/tree/master/lib).

### Building System

I believe that most [GitHub](https://github.com) users have tried to install software from source build. But how many of them had ever understood how the building systems of those projects are like? So this project will show you the greatest utility of [GNU Make](https://www.gnu.org/software/make "GNU Make Homepage") in the way it builds an Operating System.

This is project contains only one **Makefile**. It really makes up challenge to my ability of organizing code. This is also the only project I created without an IDE.

### Source Tree

```
TravorOS
|-- AUTHORS
|-- BIBLIOGRAPHY
|-- bochsrc
|-- boot
|   |-- 32bit
|   |   |-- gdt.asm
|   |   |-- print.asm
|   |   `-- protectedmode.asm
|   |-- bootload.asm
|   |-- disk.asm
|   |-- io.asm
|   |-- Makefile
|   `-- screen.asm
|-- BUILDING.md
|-- ChangeLog.md
|-- debug.gdb
|-- demos
|   |-- iodemo.asm
|   |-- license
|   |-- numbergame
|   |-- numbergame.c
|   `-- video.c
|-- drivers
|   |-- idt.c
|   |-- interrupt.asm
|   |-- isr.c
|   |-- kbd.c
|   |-- Makefile
|   `-- screen.c
|-- include
|   |-- asm
|   |   |-- interrupt.h
|   |   `-- ioports.h
|   |-- ctypes.h
|   |-- def.h
|   |-- drivers
|   |   |-- idt.h
|   |   |-- isr.h
|   |   |-- kbd.h
|   |   `-- screen.h
|   |-- fibonacci.h
|   |-- io.h
|   |-- misc.h
|   |-- random.h
|   |-- stdio.h
|   |-- string.h
|   `-- types.h
|-- kernel
|   |-- kernel.c
|   |-- kernel_entry.asm
|   `-- Makefile
|-- lib
|   |-- conv.c
|   |-- ctypes.c
|   |-- fibonacci.c
|   |-- hex.c
|   |-- io.c
|   |-- lowlevel.asm
|   |-- printf.c
|   |-- random.c
|   `-- string.c
|-- LICENSE
|-- Makefile
|-- README.md
`-- vars.mak
```
