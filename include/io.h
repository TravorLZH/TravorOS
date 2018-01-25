#include <screen.h>
#ifndef __IO_H_
#define	__IO_H_
#define	puts(a)	print_at(a,-1,-1,0x07)
#define	putchar(c)	print_char(c,-1,-1,0x07)
#ifdef	__cplusplus
extern	"C"{
#endif
extern char getchar(void);
#ifdef	__cplusplus
}
#endif
#endif

