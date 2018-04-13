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
static inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0"
			: "=a"(ret)
			: "Nd"(port) );
	return ret;
}

static inline void outw(uint16_t port, uint16_t val)
{
	asm volatile ( "outw %0, %1" : : "a"(val),"Nd"(port));
}

static inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile ("inw %1,%0" : "=a"(ret) : "Nd" (port));
	return ret;
}
#ifdef	__cplusplus
}
#endif
#endif
