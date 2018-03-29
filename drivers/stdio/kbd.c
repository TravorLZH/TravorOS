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
static char kb_interrupt=0;
static char special=0;
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
char code2char(unsigned char code){
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
char getScancode(){
	/*char flag=port_byte_in(0x64);
	  while(!(flag & 1)){
	  flag=port_byte_in(0x64);
	  }*/
	while(!kb_interrupt || special);
	kb_interrupt=0;
	return port_byte_in(0x60);
}

void keyboard_handler(registers_t r){
	int x=port_byte_in(0x60);
	char code;
	kb_interrupt=1;
	special=0;
	if(x & 0x80){
		// TODO: Handler when key is released.
		code=code2char(x-0x80);
		if(code==VK_SHIFT){
			special=1;
			shift=0;
		}
		if(code==VK_CONTROL){
			special=1;
			ctrl=0;
		}
		if(code==VK_MENU){
			special=1;
			alt=0;
		}
	}else{
		code=code2char(x);
		if(code==VK_SHIFT){
			special=1;
			shift=1;
			return;
		}
		if(code==VK_CONTROL){
			special=1;
			ctrl=1;
		}
		if(code==VK_MENU){
			special=1;
			alt=1;
		}
		if(code==VK_CAPITAL){
			special=1;
			capital=capital==1 ? 0 : 1;
			return;
		}
		//putchar(code);
	}
}

void init_keyboard(){
	kprint("Initializing keyboard ...");
	register_interrupt_handler(0x21,keyboard_handler);
	print_at("[OK]\n",-1,-1,0x02);
}

