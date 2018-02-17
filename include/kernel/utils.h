#ifndef	__UTILS_H_
#define	__UTILS_H_
#define	kprint(...)	__kprintf("[kernel]: " __VA_ARGS__)
#ifdef	__cplusplus
extern int __kprintf(const char* str,...);
#endif
#endif
