#include <string.h>
#include <api.h>

char* video_mem=(char*)0xb8000;
int strlen(const char* str){
	const char *s;
	for(s=str;*s;++s);
	return (s-str);
}
int putchar(char c){
	int ret=_api_putchar(video_mem,c,0x0F);
	video_mem+=2;
	return ret;
}
int puts(const char* s){
	int i=0;
	if(strlen(s)==0)return 1;
	for(;i<strlen(s);i++){
		putchar(*(s+i));
	}
	return 0;
}
