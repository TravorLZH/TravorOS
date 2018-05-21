/* printf.c: Formating string using variable arguments */
#include <kernel/utils.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

char *pad_zero(int num,char *str)
{
	int len=strlen(str);
	int diff=num-len;
	if(diff<=0){
		return str;
	}
	char zeroes[diff+1];
	char tmp[num+1];
	memset(zeroes,'0',diff);
	zeroes[diff]='\0';
	memset(tmp,0,len+1);
	sprintf(tmp,"%s%s",zeroes,str);
	strcpy(str,tmp);
}

// formatting string: The fundamental function of printf family.
int vsprintf(char* buffer,const char *format,va_list vlist)
{
	// TODO: Implementations
	int int_temp;
	size_t uint_temp;
	char char_temp;
	char* string_temp;
	char buf_temp[BUFSIZ];

	char ch;
	size_t offset=0;

	int len=0;
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
				len=strlen(buf_temp);
				memcpy(buffer+offset,buf_temp,len);
				offset+=len;
				break;
				// Print an unsigned int
				case 'u':
				uint_temp=va_arg(vlist,size_t);
				utoa(uint_temp,buf_temp);
				len=strlen(buf_temp);
				memcpy(buffer+offset,buf_temp,len);
				offset+=len;
				break;
				// Print hex values
				case 'x':
				int_temp=va_arg(vlist,int);
				itoh(int_temp,buf_temp);
				len=strlen(buf_temp);
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
int sprintf(char* buf,const char* fmt,...)
{
	va_list vl;
	va_start(vl,fmt);
	int rs=vsprintf(buf,fmt,vl);
	va_end(vl);
	return rs;
}
int vprintf(const char* fmt,va_list vlist)
{
	char buf[BUFSIZ];
	int rs=vsprintf(buf,fmt,vlist);
	puts(buf);
	return rs;
}
int printf(const char* fmt,...)
{
	va_list vl;
	va_start(vl,fmt);
	int rs=vprintf(fmt,vl);
	va_end(vl);
	return rs;
}
