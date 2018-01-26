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
int atoi(const char* nptr){
	char* x=(char*)nptr;
	int res=0;
	int sign=1;
	int i=0;
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

long atol(const char* nptr){
	char* s=(char*)nptr;
	size_t i;
	long n=0L;
	char sign;
	for(i=0;isspace(s[i]);i++){
		sign=(s[i] == '-') ? -1 : 1;
		if(sign=='-' || sign=='+')i++;
	}
	for(;isdigit(s[i]);i++){
		n=10*n+(s[i]-'0');
	}
	return n*sign;
}

long long atoll(const char* nptr){
	char* s=(char*)nptr;
	size_t i;
	long long n=0LL;
	char sign;
	for(i=0;isspace(s[i]);i++){
		sign=(s[i] == '-') ? -1 : 1;
		if(sign=='-' || sign=='+')i++;
	}
	for(;isdigit(s[i]);i++){
		n=10*n+(s[i]-'0');
	}
	return n*sign;
}

// Integer -> String
void itoa(int n,char *s){
	size_t i;
	int j;
	char sign;	// 1: negative, 0: positive
	// TODO: Record the sign of the integer
	if(n<0){
		n=-n;
		sign=1;
	}
	i=0;
	do{
		s[i++]=n%10+'0';
	}while((n/=10)>0);
	if(s[i]=='0'&&i>0){	// If there is zero before the number,
		s[i]='\0';		// change it to the end of string
	}
	s=strrev(s);
}

