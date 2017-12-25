/* misc.h: It contains some fundamental standard and not standard C functions which are implemented by myself. */
#include <types.h>
#ifndef	__MISC_H_
#define	__MISC_H_
// Basic constants
#define	NULL	0
#define	EOF		-1
#define	TRUE	1
#define	FALSE	0
#ifdef	__cplusplus
extern "C"{
#endif
// These should be in ctypes.h
extern int isalpha(int c);
extern int isdigit(int c);
extern int isgraph(int c);
extern int isprint(int c);
extern int ispunct(int c);
extern int isspace(int c);

extern int islower(int c);
extern int isupper(int c);

extern int tolower(int c);
extern int toupper(int c);

// String function
extern char* strchr(const char*,int c);
extern char* strcpy(char* dest,char* src);
extern unsigned int strlen(const char*);

// Conversion functions
extern int atoi(const char *nptr);
extern long atol(const char *nptr);
extern long long atoll(const char *nptr);

// Memory function
extern void* memcpy(void* dest,const void* src,size_t n);

// Not standard functions
extern int ch2int(char c);
extern int int2ch(int i);
#ifdef	__cplusplus
}
#endif
#endif
