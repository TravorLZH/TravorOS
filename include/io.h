/* 
* TravorOS: A simple OS running on Intel x86 Architecture
* Copyright (C) 2017  Travor Liu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* io.h: Basic screen I/O functions */
#include <drivers/screen.h>
#ifndef __IO_H_
#define	__IO_H_
#define	puts(a)	print_at((const char*)(a),-1,-1,0x07)
#define	putchar(c)	print_char((c),-1,-1,0x07)
#ifdef	__cplusplus
extern	"C"{
#endif
extern char getchar(void);
extern char* gets(char* str);
#ifdef	__cplusplus
}
#endif
#endif

