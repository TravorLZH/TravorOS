#include <stdio.h>
#include <string.h>
#include <kernel/syscall.h>
#include <drivers/screen.h>

static char *userbuf=NULL;
volatile char flushed=0;

int puts(const char *s)
{
	sys_puts(s);
	return 1;
}

int putchar(int c)
{
	sys_putchar(c);
	return c;
}

static void my_flush_handler(const char *buf){
	flushed=1;
	if(userbuf!=NULL){
		strcpy(userbuf,buf);
	}
}

char *gets(char *s){
	userbuf=s;
	kbd_flush_handler(my_flush_handler);
	while(!flushed);
	flushed=0;
	return userbuf;
}
