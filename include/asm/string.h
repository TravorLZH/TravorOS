/* asm/string.h: x86 alternative for string functions */
#ifndef	__STRING_H_
#define	__STRING_H_
#include <def.h>
#ifdef	__cplusplus
static	"C"{
#endif
static inline int strlen(const char *s)
{
	int ret;
	__asm__("xor	%%ecx,%%ecx\n\t"
		"not	%%ecx\n\t"
		"xor	%%al,%%al\n\t"
		"cld\n\t"
		"repne	scasb\n\t"
		"not	%%ecx\n\t"
		"dec	%%ecx\n\t":"=c"(ret):"D"(s));
	return ret;
}
static inline char *strcpy(char *dest,const char *src)
{
	__asm__("cld\n"
		"1:\tlodsb\n\t"
		"stosb\n\t"
		"test	%%al,%%al\n\t"
		"jne	1b"
		::"S"(src),"D"(dest):"esi","edi","eax");
	return  dest;
}
static inline char *strncpy(char *dest,const char *src,int count){
	__asm__("cld\n"
		"1:\tdecl	%2\n\t"
		"js	2f\n\t"
		"lodsb\n\t"
		"stosb\n\t"
		"testb	%%al,%%al\n\t"
		"jne	1b\n\t"
		"rep	stosb\n\t"
		"2:"
		::"S"(src),"D"(dest),"c"(count):"esi","edi","eax","ecx");
	return dest;
}
static inline void *memcpy(void *dest,const void *src,size_t count){
	__asm__("rep movsd"
		::"S"(src),"D"(dest),"c"(count >> 2):"memory");
	__asm__("rep movsb"
		::"S"(src),"D"(dest),"c"(count & 7):"memory");
	return dest;
}
static inline void *memset(void *dest,int c,size_t count){
	__asm__("cld\n"
		"rep stosb"
		::"D"(dest),"a"(c),"c"(count):"memory");
	return dest;
}
#ifdef	__cplusplus
}
#endif
#endif
