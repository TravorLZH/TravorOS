/* string.h: String and Memory Functions */
#include <def.h>
#ifndef	__STRING_H_
#define	__STRING_H_
#ifdef	__cplusplus
extern	"C"{
#endif
// String functions
extern char *strchr(const char*,int c);
extern char *strcpy(char* dest,const char* src);
extern unsigned int strlen(const char*);
/* Not standard string function(s) */
extern char *strrev(char *str);
extern char *pad_zero(int num,char *str);

extern void *memcpy(void *dest,const void *src,size_t len);
extern void *memmove(void *dest,const void *src,size_t len);
extern int memcmp(const void *p1,const void *p2,size_t len);
#ifdef	__cplusplus
}
#endif
#endif
