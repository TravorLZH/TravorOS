#ifndef	__STDIO_H_
#define	__STDIO_H_
#include <def.h>
#include <stdarg.h>
#ifdef	__cplusplus
extern	"C"{
#endif
// printf family
extern int printf(const char* fmt,...);
extern int vprintf(const char* fmt,va_list vlist);
extern int sprintf(char *buf,const char *fmt,...);
extern int vsprintf(char* buf,const char *fmt,va_list vlist);
// Basic I/O functions
extern char *gets(char *s);
extern int puts(const char *s);
extern int putchar(int c);
#ifdef	__cplusplus
}
#endif
#endif
