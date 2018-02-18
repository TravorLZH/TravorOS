Building TravorOS
=======

## Linux

To build this Operating System in Linux or Windows with WSL, type
```
make
```
## Cygwin with [Cross Compiler][crosscompiler]

Modify `Makefile`.

Original:
```Makefile
AS=yasm
GCC=gcc
LD=ld
```
Modified:
```Makefile
AS=yasm -DMINGW
GCC=gcc
LD=i386-elf-ld
```

At last type `make`.

> This method has not been successful because its linker pops up error. See also Issue #1 .

[crosscompiler]: https://github.com/nativeos/i386-elf-toolchain/releases
