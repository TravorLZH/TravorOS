#include <def.h>
#ifndef	__BSOD_H_
#define	__BSOD_H_
#ifdef	__cplusplus
extern	"C"{
#endif
extern void bsod_enter(size_t int_no,const char *name,size_t err_no,const char *description,size_t eip);
#ifdef	__cplusplus
}
#endif
#endif
