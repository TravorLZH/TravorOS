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
#include <drivers/kbd.h>
#include <drivers/screen.h>
#include <asm/ioports.h>
#include <kernel/utils.h>
#include <ctypes.h>
#include <cpu/isr.h>
/* kbd.c: A simple keyboard driver */

// Flags for key pressed
static char ctrl=0;
static char alt=0;
static char shift=0;
static char capital=0;
static volatile char kb_interrupt=0;	// Make sure this is not erased by compiler
// Table for scan code character mappings
const char press_char[]={
	VK_ESCAPE,'1','2','3','4','5','6','7','8','9','0','-','=',VK_BACK,
	VK_TAB,'q','w','e','r','t','y','u','i','o','p','[',']',VK_RETURN,
	VK_CONTROL,'a','s','d','f','g','h','j','k','l',';','\'','`',VK_SHIFT,
	'\\','z','x','c','v','b','n','m',',','.','/',VK_SHIFT,'*',VK_MENU,
	VK_SPACE,VK_CAPITAL,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8,VK_F9,VK_F10
};
const char shift_char[]={
	VK_ESCAPE,'!','@','#','$','%','^','&','*','(',')','_','+',VK_BACK,
	VK_TAB,'Q','W','E','R','T','Y','U','I','O','P','{','}',VK_RETURN,
	VK_CONTROL,'A','S','D','F','G','H','J','K','L',':','"','~',VK_SHIFT,
	'|','Z','X','C','V','B','N','M','<','>','?',VK_SHIFT,'*',VK_MENU,
	VK_SPACE,VK_CAPITAL,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8,VK_F9,VK_F10
};
inline char code2char(unsigned char code){
	char r;
	if(shift==1){
		r=shift_char[code-1];
		if(capital==1 && (r>='A' && r<='Z')){
			r=r-'A'+'a';
		}
	}else{
		r=press_char[code-1];
		if(capital==1 && (r>='a' && r<='z')){
			r=r-'a'+'A';
		}
	}
	return r;
}
char _getchar(){
	unsigned char code=0;
	while(1){
		code=getScancode();
		if(code>=0x80){
			continue;
		}
		break;
	}
	return code2char(code);
}
inline char getScancode(){
redo:
	while(!kb_interrupt);
	kb_interrupt=0;
	switch(inb(0x60)){
		case VK_SPACE:case VK_MENU:case VK_CONTROL:case VK_SHIFT:
		goto redo;
	}
	return inb(0x60);
}

void keyboard_handler(registers_t r){
	int x=port_byte_in(0x60);
	kb_interrupt=1;
	if(x & 0x80){
		outb(0x20,0x20);
		switch(code2char(x)){
			case VK_SHIFT:
			shift=0;
			break;
			case VK_CONTROL:
			ctrl=0;
			break;
			case VK_MENU:
			alt=0;
			break;
		}
	}else{
		switch(code2char(x)){
			case VK_SHIFT:
			shift=1;
			break;
			case VK_CONTROL:
			ctrl=1;
			break;
			case VK_MENU:
			alt=1;
			break;
			case VK_CAPITAL:
			capital=capital==1 ? 0 : 1;
			break;
		}
	}
}

void init_keyboard(){
	kprint("Initializing keyboard ...");
	register_interrupt_handler(0x21,keyboard_handler);
	print_at("[OK]\n",-1,-1,0x02);
}
