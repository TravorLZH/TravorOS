#include <def.h>
#ifndef	__IOPORTS_H_
#define	__IOPORTS_H_
#define	port_byte_in	inb
#define	port_byte_out	outb
#ifdef	__cplusplus
extern	"C"{
#endif
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port,uint8_t val);
#ifdef	__cplusplus
}
#endif
#endif

