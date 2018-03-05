#ifndef	__UTILS_H_
#define	__UTILS_H_
#define	kprint(...)	__kprintf("[kernel]: " __VA_ARGS__)
#define	PANIC(...)	kprint("Panic: " __VA_ARGS__);while(1)
#ifdef	__cplusplus
extern int __kprintf(const char* str,...);
#endif
#endif
