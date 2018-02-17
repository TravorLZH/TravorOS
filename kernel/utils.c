#include <stdarg.h>
#include <def.h>
#include <kernel/utils.h>
#include <drivers/screen.h>

int __kprintf(const char* str,...){
	va_list vlist;
	va_start(vlist,str);
	char s[BUFSIZ];
	int ret=vsprintf(s,str,vlist);
	print_at(s,-1,-1,0x0F);
	va_end(vlist);
	return ret;
}
