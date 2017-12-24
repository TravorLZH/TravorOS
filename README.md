# TravorOS - Developing with Simplification

This is the first [Operating System](https://en.wikipedia.org/wiki/Operating_System "Operating System Definition") I created. It's written in two languages: C language and Assembly.

This project has been activated since [December 15, 2017](https://github.com/TravorLZH/TravorOS/blob/master/ChangeLog.md#0-1-r0-2017-12-15)

### Bootloader

This OS uses a bootloader that switches from `16-bit real mode` to `32-bit protected mode`. It loads kernel code into memory before it entered 32-bit protected mode.

### Kernel

It's written in C. It simply calls other C standard functions that I implemented myself in [lib](https://github.com/TravorLZH/TravorOS/tree/master/lib).

### Building System

I believe that most [GitHub](https://github.com) users have tried to install software from source build. But how many of them had ever understood how the building systems of those projects are like? So this project will show you the greatest utility of [GNU Make](https://www.gnu.org/software/make "GNU Make Homepage") in the way it builds an Operating System.

The sources are separated into ５ folders.

- `boot`: This folder contains the code of bootloader especially the conversion from `16-bit real mode` to `32-bit protected mode`.

- `kernel`: This folder contains the most important part of the Operating System -- the code of KERNEL which is written in C.

- `drivers`: It contains a lot of important components of the kernel, the code inside will be statically linked with the `kernel`.

- `lib`: It contains some basic functions used by kernel, but it's still a little bit.

- `include`: It contains C headers of the drivers and remainder of `libbc`. I organized string operations into [string.h](https://github.com/TravorLZH/TravorOS/blob/master/include/string.h), and the rest in [basic.h](https://github.com/TravorLZH/TravorOS/blob/master/include/basic.h). System calls are declared in [api.h](https://github.com/TravorLZH/TravorOS/blob/master/include/api.h).

This is project contains only ｓｅｖｅｒａｌ `Makefile`ｓ. It really makes up challenge to my ability of organizing code. At first, I used multiple `Makefile` in each folder, but now I get rid of that. I can simplify this project more!
