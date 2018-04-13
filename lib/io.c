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
#include <string.h>
#include <drivers/screen.h>
#include <io.h>

char getchar(void)
{
	char c=_getchar();
	print_char(c,-1,-1,0x07);
	return c;
}

static void append(char *buf,char c)
{
	size_t len=strlen(buf);
	if(c=='\b'){
		buf[len-1]='\0';
		return;
	}
	buf[len]=c;
	buf[len+1]='\0';
}

char* gets(char* s)
{
	char* st=s;
	char c;
	while((c=getchar())!='\n'){
		append(s,c);
	}
	// Only if there is a problem, code will go here
	return s;
}

