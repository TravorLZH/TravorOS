# ChangeLog

All major changes will be added in this file

## Debugging (Pre-release)

### 0.1-r0 2017-12-15
#### Added

- Migrated all files from [kerneltest32](https://github.com/TravorLZH/OSLEARN/tree/master/kerneltest32)

### 0.1-r1 2017-12-15
#### Added

- `types.h`: Definitions of `int*_t` and `size_t`, this will make my `libc` porting easier.

- `mem.asm`: Implementations of `memcpy` and `memmove`.

- `memory.h`: Contains functions `memcpy` and `memmove`.

#### Modified

- `string.h`: Includes `memory.h`. This made my C language more like the [standard](https://en.wikipedia.org/wiki/ANSI_C "ANSI C"). Also new function `strcpy	.

- `basic.c`: Added implementations of listed functions.

