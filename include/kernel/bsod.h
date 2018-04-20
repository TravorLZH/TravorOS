#ifndef	__BSOD_H_
#define	__BSOD_H_
#include <def.h>
#include <cpu/isr.h>
#ifdef	__cplusplus
extern	"C"{
#endif
extern void bsod_enter(const char *name,const char *description,registers_t *regs);
#ifdef	__cplusplus
}
#endif
#endif
