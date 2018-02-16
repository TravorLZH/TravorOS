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
/* misc.h: It contains some fundamental standard and not standard C functions which are implemented by myself. */
#include <random.h>
#include <drivers/screen.h>
#include <io.h>

char getchar(void){
	char c=_getchar();
	putchar(c);
	return c;
}

char* gets(char* s){
	char* st=s;
	char temp,term,asterisk,skip,skip_print;
	while(1){
		temp=_getchar();
		skip=0; // Reset the skip flag
		term=0;
		skip_print=0;
		asterisk=0;
		// I use switch because there might be more special characters
		switch(temp){
		case '\b':
			if(st==s){
				//asterisk=1;
				skip_print=1;
				break;
			}
			st--;
			*st=0;
			skip=1;
			break;
			case '\n':
			term=1;
			break;
		}
		if(skip_print==1)continue;
		putchar(temp);
		if(asterisk==1)print_char('*',-1,-1,0x0F);
		if(skip==1)continue; // If there is a problem, skip the following
		if(term==1){
			*st=0;
			return st;
		}
		// TODO: Store the character into the string
		*st=temp;
		st++;
	}
	// Only if there is a problem, code will go here
	return 0;
}

