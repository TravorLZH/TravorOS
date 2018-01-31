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
/* vsprintf.c: Formating string using variable arguments */
#include <stdarg.h>
#include <stdio.h>

// formatting string: The fundamental function of printf family.
int vsprintf(char* buffer,const char *format,va_list vlist){
	// TODO: Implementations
	int int_temp;
	char char_temp;
	char* string_temp;
	char buf_temp[BUFSIZ];

	char ch;
	size_t offset=0;

	while(ch=*(format++)){
		if('%'==ch){
			switch(ch=*format++){
				// %%
				case '%':
				*(buffer+offset)='%';
				offset++;
				break;
				// %c: Print out character
				case 'c':
				*(buffer+offset)=va_arg(vlist,int);
				offset++;
				break;
				// %s: Print out string
				case 's':
				string_temp=va_arg(vlist,char*);
				memcpy(buffer+offset,string_temp,strlen(string_temp));
				offset+=strlen(string_temp);
				break;
				// Print out an int
				case 'd':
				int_temp=va_arg(vlist,int);
				itoa(int_temp,buf_temp);
				int len=strlen(buf_temp);
				memcpy(buffer+offset,buf_temp,len);
				offset+=len;
				break;
			}
		}else{
			*(buffer+offset)=ch;
			offset++;
		}
	}
	*(buffer+offset)='\0';	// Null Terminator
	return offset;
}
int sprintf(char* buf,const char* fmt,...){
	va_list vl;
	va_start(vl,fmt);
	int rs=vsprintf(buf,fmt,vl);
	va_end(vl);
	return rs;
}
int vprintf(const char* fmt,va_list vlist){
	char buf[BUFSIZ];
	int rs=vsprintf(buf,fmt,vlist);
	puts(buf);
	return rs;
}
int printf(const char* fmt,...){
	va_list vl;
	va_start(vl,fmt);
	int rs=vprintf(fmt,vl);
	va_end(vl);
	return rs;
}

