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
/* conv.c: Implementations of conversion functions */
#include <misc.h>

// The following code is about the conversion between string and variety of integers.
// I partially refer the 1st link in BIBLIOGRAPHY
/* String -> Integer */
int atoi(const char* nptr)
{
	char* x=(char*)nptr;
	int res=0;
	int sign=1;
	if(x[0]=='-'){
		sign=-1;
		x++;
	}else if(x[0]=='+'){
		x++;
	}
	char* s=x+strlen(x);
	while(x<s){
		res=res*10+*x-'0';
		x++;
	}
	return sign*res;
}

// Integer -> String
void itoa(int n,char *s)
{
	char neg=0;
	char *x=s;
	if(n<0){
		neg=1;
		n=-n;
	}
	do{
		*x=n%10+'0';
		x++;
	}while(n/=10);
	if(neg){
		*x='-';
		x++;
	}
	*x='\0';
	strrev(s);
}

void utoa(size_t n,char *s)
{
	char *x=s;
	do{
		*x=n%10+'0';
		x++;
	}while(n/=10);
	*x='\0';
	strrev(s);
}
