#include <string.h>
#include <api.h>

char* video_mem=(char*)0xb8000;
int strlen(const char* str){
	const char *s;
	for(s=str;*s;++s);
	return (s-str);
}
void* strcpy(char* dest,const char* src){
	return memcpy(dest,src,strlen(src));
}
int putchar(char c){
	int ret=_api_putchar(video_mem,c,0x0F);
	video_mem+=2;
	return ret;
}
int puts(const char* s){
	int i=0;
	for(;*(s+i);i++){
		putchar(*(s+i));
	}
	return 0;
}
