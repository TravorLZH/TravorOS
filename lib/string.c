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
#include <string.h>

char* strcat(char* s1,char* s2){
	char* s1_end=s1+strlen(s1);
	strcpy(s1_end,s2);
	return s1;
}

char* strchr(const char *s,int c){
	char* str=(char*)s;
	while(str++){
		if(*str==(char)c){
			return str;
		}
	}
	return NULL;
}

char* strcpy(char* dest,char* src){
	return (char*)memcpy(dest,src,sizeof(src));
}

size_t strlen(const char* str)
{
	size_t i=0;
	for(;str[i];i++);
	return i;
}

char* strrev(char* str){
	char* start=str;
	char* end=str;
	char temp=0;
	while(*(end++));
	end--;	// Compensate end++
	end--;	// Ignore the \0
	while(start<end){
		temp=*start;
		*start++=*end;
		*end--=temp;
	}
	return str;
}

int strcmp(const char* s1,const char* s2)
{
	int i=0;
	for(;;i++){
		if(s1[i]!=s2[i]){
			return s1[i] < s2[i] ? -1 : 1;
		}
		if(s1[i]=='\0'){
			return 0;
		}
	}
}

void *memcpy(void *dest,const void *src,size_t n){
	char* d=(char*)dest;
	char* s=(char*)src;
	int i=0;
	for(;i<n;i++){
		*(d+i)=*(s+i);
	}
	return dest;
}

void *memmove(void *dest,const void *src,size_t n){
	char *d=(char*)dest;
	char *s=(char*)src;
	char tmp[n];
	memcpy(tmp,s,n);
	memcpy(d,tmp,n);
	return d;
}

void *memset(void *dest,int ch,size_t count){
	char* ptr=dest+count;
	char c=(char)ch;
	while(count--){
		*ptr=c;
		ptr--;
	}
	return dest;
}

int memcmp(const void *p1,const void *p2,size_t n)
{
	char *pa=(char*)p1;
	char *pb=(char*)p2;
	int i=0;
	int ret=0;
	for(;n--;pa++,pb++){
		if(*pa!=*pb){
			return *pa-*pb;
		}
	}
	return 0;
}
