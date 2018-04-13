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
#ifdef	__cplusplus
}
#endif
#endif
