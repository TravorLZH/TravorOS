# ChangeLog

All major changes will be added in this file.

## Debugging (Pre-release)
### 0.2-r1 2017-12-25

This revision added a lot of features on library.

### Added

- `demos`: Some little bootloaders or C programs I created for testing my basic knowledge. <strong>They are not promised to run properly</strong>

- `lib`, `lib/libbc/`, `libbc/string.c`, `include/misc.h`: They are the new functions I created for C library. `libbc` stands for `Basic C library`. Now it contains some generic string operations. Later I will add `printf` family.

### Modified

- `Makefile`s: I changed the assembler from `NASM` to `YASM`, this allows users to build and emulate this OS on phone using [Termux](https://termux.com/) and [Limbo PC Emulator](https://play.google.com/store/apps/details?id=fr.energycube.android.app.com.limbo.emu.main.armv7).

### 0.2-r0 2017-12-18

This revision would be a tag in this repo.

#### Added

- `drivers`: An improved substitution for the obsolete libraries. You may tell many similarity of the code from the document in [LearnOS][1]

- `drivers/screen.c`, `drivers/screen.h`: Features about screen (text, cursor, etc.). They will play a big role on this OS.

#### Modified

- `Building System`: Because I removed the individual library, I will remove those individual `Makefile`s in order to simplify this project.

#### Removed

- `lib`: Inadequate part of my OS. It currently contains one library `io` which has some lower functions written with inline assembly

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
