#ifndef	__IOPORTS_H_
#define	__IOPORTS_H_
#define	port_byte_in	inb
#define	port_byte_out	outb
#ifdef	__cplusplus
extern	"C"{
#endif
extern char inb(unsigned short port);
extern char outb(unsigned short port,char val);
#ifdef	__cplusplus
}
#endif
#endif

