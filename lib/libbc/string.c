#include <misc.h>

char* alpha="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* digit="0123456789";
char* punct="!\"#$%&'()*+,-./:;<=>@[\\]^_`{|}~";
char* space="\t\n\r ";

int isalpha(int c){
	if(strchr(alpha,c)){
		return TRUE;
	}
	return FALSE;
}

int isdigit(int c){
	if(c==EOF)return FALSE;
	if(strchr(digit,c)){
		return TRUE;
	}
	return FALSE;
}

int ispunct(int c){
	if(strchr(punct,c)){
		return TRUE;
	}
	return FALSE;
}

int islower(int c){
	if(c>='a' && c<='z'){
		return TRUE;
	}
}

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

size_t strlen(const char* str){
	char* s=(char*)str;
	while(s++);
	return s-str;
}

int isupper(int c){
	if(c>='A' && c<='Z'){
		return TRUE;
	}
	return FALSE;
}

void* memcpy(void* dest,const void* src,size_t n){
	int i=0;
	for(;i<n;i++){
		*((char*)dest+i)=*((char*)src+i);
	}
	return dest;
}

int atoi(const char* nptr){
	char* s=(char*)nptr;
	char positive=1;	// The number will be positive or negative.
	int num=0;			// The converted number
	// TODO: Conversion Operation
	while(s++){
		
	}
	return num;
}
