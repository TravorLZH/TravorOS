#ifndef	__INTERRUPT_H_
#define	__INTERRUPT_H_
#define	sti()	set_interrupt()
#define	cli()	clear_interrupt()
#ifdef	__cplusplus
extern	"C"{
#endif
static inline char set_interrupt(void)
{
	__asm__("sti");
}
static inline char clear_interrupt(void)
{
	__asm__("cli");
}
#ifdef	__cplusplus
}
#endif
#endif
