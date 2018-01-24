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
/* kernel.c: The core part of the OS kernel (i.e. The heart of the OS) */
#include <misc.h>
#include <kbd.h>
#include <screen.h>

#define	puts(a)	print_at(a,-1,-1,0x07)
#define	putchar(c)	print_char(c,-1,-1,0x07)

#define	COLOR	0x70

void _sleep(long long sec){
	sec*=10000;
	while(sec--);
}

int main(void){
	while(1){
		putchar(_getchar());
	}
	return 0;
}
