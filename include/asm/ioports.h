#include <def.h>
#ifndef	__IOPORTS_H_
#define	__IOPORTS_H_
#define	port_byte_in	inb
#define	port_byte_out	outb
#define	port_word_in	inw
#define	port_word_out	outw
#ifdef	__cplusplus
extern	"C"{
#endif
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port,uint8_t val);
extern uint16_t inw(uint16_t port);
extern void outw(uint16_t port,uint16_t val);
#ifdef	__cplusplus
}
#endif
#endif
