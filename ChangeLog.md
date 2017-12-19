# ChangeLog

All major changes will be added in this file

## Debugging (Pre-release)

### 0.2-r0 2017-12-18

#### Added

- `drivers`: An improved substitution for the obsolete libraries. You may tell many similarity of the code from the document in [LearnOS][1]

- `drivers/screen.c`, `drivers/screen.h`: They are new replacement for `libbc`, and they will be directly linked into kernel instead of individual libraries.

#### Modified

- `Building System`: Because I removed the individual library, I will remove those individual `Makefile`s in order to simplify this project.

#### Removed

- `lib`: I decided to use `drivers` to substitute this part because I haven't got chance to build a C interface for `TravorOS` applications.

#### Purpose

As you can see in the [LearnOS][1] repo, this single `Makefile` policy is to synchronize with the `os-dev.pdf`. This change will be extremely influential in my opinion.

[1]: https://github.com/TravorLZH/LearnOS

### 0.1-r1 2017-12-15

#### Added

- `types.h`: Definitions of `int*_t` and `size_t`, this will make my `libc` porting easier.

- `mem.asm`: Implementations of `memcpy` and `memmove`.

- `memory.h`: Contains functions `memcpy` and `memmove`.

#### Modified

- `string.h`: Includes `memory.h`. This made my C language more like the [standard](https://en.wikipedia.org/wiki/ANSI_C "ANSI C"). Also new function `strcpy`.

- `basic.c`: Added implementations of listed functions.

### 0.1-r0 2017-12-15

#### Added

- Migrated all files from [kerneltest32](https://github.com/TravorLZH/OSLEARN/tree/master/kerneltest32)
