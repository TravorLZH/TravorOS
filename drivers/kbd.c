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
#include <kbd.h>
#include <stdio.h>
#include <isr.h>
/* kbd.c: A simple keyboard driver */

// Table for scan code character mappings
const char press_char[]={
	VK_ESCAPE,'1','2','3','4','5','6','7','8','9','0','-','=',VK_BACK,
	VK_TAB,'q','w','e','r','t','y','u','i','o','p','[',']',VK_RETURN,
	VK_CONTROL,'a','s','d','f','g','h','j','k','l',';','\'','`',VK_SHIFT,
	'\\','z','x','c','v','b','n','m',',','.','/',VK_SHIFT,'*',VK_MENU,
	VK_SPACE,VK_CAPITAL,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8,VK_F9,VK_F10
};
char code2char(unsigned char code){
	return press_char[code-1];
}
char _getchar(){
	unsigned char code=0;
	while(1){
		code=getScancode();
		if(code>=sizeof(press_char)-1){
			continue;
		}
		break;
	}
	return code2char(code);
}
char getScancode(){
	char flag=port_byte_in(0x64);
	while(!(flag & 1)){
		flag=port_byte_in(0x64);
	}
	return port_byte_in(0x60);
}

void keyboard_handler(registers_t r){
	int x=port_byte_in(0x60);
	if(x<0x80){
		putchar(code2char(x));
	}
}

void init_keyboard(){
	register_interrupt_handler(0x21,keyboard_handler);
}

