#ifndef	__SYSCALL_H_
#define	__SYSCALL_H_
#ifdef	__cplusplus
extern	"C"{
#endif
static inline void sys_puts(const char *str)
{
	__asm__("int	$0x80"::"a"(5),"S"(str));
}
static inline void sys_putchar(char c)
{
	__asm__("int	$0x80"::"a"(6),"b"(c));
}
#ifdef	__cplusplus
}
#endif
#endif
