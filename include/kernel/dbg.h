#include <kernel/utils.h>
#ifndef	__DBG_H_
#define	__DBG_H_
#ifndef	NDEBUG
#ifdef	__cplusplus
extern	"C"{
#endif
#define	kassert(expr)	(void)((expr) || (__assert(#expr,__FILE__,__LINE__),0))
#define ktrace(...)	kprint("TRACING: " __VA_ARGS__)
extern void __assert(const char* msg,const char* file, int line);
#else
#define	kassert(expr)
#define	ktrace(...)
#endif
#endif

