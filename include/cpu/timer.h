#include <def.h>
#ifndef	__TIMER_H_
#define	__TIMER_H_
#ifdef	__cplusplus
extern	"C"{
#endif
extern void delay(size_t ticks);
extern void init_timer(size_t freq);
#ifdef	__cplusplus
}
#endif
#endif
