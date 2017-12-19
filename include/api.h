#include <types.h>
#ifndef	__API_H_
#define	__API_H_
#ifdef	__cplusplus
extern "C"{
#endif
extern int _api_putchar(char* addr,char c,char attr);
extern int _api_movbyte(char* dest,char* src);
extern char* _api_movbytes(char* dest,char* src,size_t count);
#ifdef	__cplusplus
}
#endif
#endif
