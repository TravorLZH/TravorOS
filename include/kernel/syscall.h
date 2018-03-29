#ifndef	__SYSCALL_H_
#define	__SYSCALL_H_
#ifdef	__cplusplus
extern	"C"{
#endif
inline void sys_print(const char *str){
	__asm__("int	$0x80"::"a"(5),"S"(str));
}
#ifdef	__cplusplus
}
#endif
#endif
