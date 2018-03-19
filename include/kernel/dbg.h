#include <kernel/utils.h>
#ifndef	__DBG_H_
#define	__DBG_H_
#ifndef	NDEBUG
#ifdef	__cplusplus
extern	"C"{
#endif
#define	assert(expr)	(void)((expr) || (__assert(#expr,__FILE__,__LINE__),0))
#define ktrace(...)	kprint("%s: ",__func__);kprintf(__VA_ARGS__)
#define	printvar(expr)	ktrace("%s=%u (0x%x)\n",#expr,(expr),(expr))
extern void __assert(const char* msg,const char* file, int line);
#else
#define	printvar(expr)	expr
#define	assert(expr)
#define	ktrace(...)
#endif
#endif
