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

char* strcpy(char* dest,const char* src){
	return (char*)memcpy(dest,src,strlen(src)+1);
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
	for(;*s1==*s2;++s1,++s2)
		if(*s1==0)
			return 0;
	return *s1-*s2;
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
	int i;
	char *ptr=(char*)dest;
	char c=(char)ch;
	for(i=0;i<count;i++){
		*(ptr+i)=c;
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
