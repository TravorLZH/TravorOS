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
#include <basic_io.h>

unsigned char port_byte_in(unsigned short port){
	// A handy C wrapper for function that reads a byte from the specified port
	// "=a" (result) means: put AL register in variable RESULT when finished
	// "d" (port) means: load EDX with port
	unsigned char result;
	__asm__("in %%dx,%%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port,unsigned char data){
	// "a" (data) means: load EAX with data
	// "d" (port) means: load EDX with port
	__asm__("out %%al,%%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in(unsigned short port){
	unsigned short result;
	__asm__("in	%%dx, %%ax" : "=a" (result) : "d" (port));
}

void port_word_out(unsigned short port,unsigned short data){
	__asm__("out %%ax,%%dx" : : "a" (data), "d" (port));
}

void io_wait(void){
	__asm__("jmp 1f\n\t"
		"1: jmp 2f\n\t"
		"2:");
}
