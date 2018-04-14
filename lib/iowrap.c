#include <stdio.h>
#include <kernel/syscall.h>
#include <drivers/screen.h>

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
