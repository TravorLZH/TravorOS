#ifndef	__UTILS_H_
#define	__UTILS_H_
#ifndef	__DBG_H_
#include <kernel/dbg.h>
#endif
#define	kprint(...)	__kprintf("[kernel]: " __VA_ARGS__)
#define	PANIC(...)	kprint("Panic: " __VA_ARGS__);while(1)
#ifdef	__cplusplus
extern int __kprintf(const char* str,...);
#endif
#endif
