#ifndef	__BASIC_IO_H_
#define	__BASIC_IO_H_
#ifdef	__cplusplus
extern "C"{
#endif
extern unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port,unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port,unsigned short data);
#ifdef	__cplusplus
}
#endif
#endif
