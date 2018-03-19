#include <stdarg.h>
#include <def.h>
#include <kernel/utils.h>
#include <drivers/screen.h>

static char color=0x0F;

void kprint_set_color(char attr){
	color=attr;
}

int kprintf(const char* str,...){
	va_list vlist;
	va_start(vlist,str);
	char s[BUFSIZ];
	int ret=vsprintf(s,str,vlist);
	print_at(s,-1,-1,color);
	va_end(vlist);
	return ret;
}
