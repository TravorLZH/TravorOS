#include <types.h>
#ifndef	__BASIC_IO_H_
#define	__BASIC_IO_H_
#ifdef	__cplusplus
extern "C"{
#endif
extern uint8_t port_byte_in(uint16_t port);
extern void port_byte_out(uint16_t port,uint8_t data);
extern uint16_t port_word_in(uint16_t port);
extern void port_word_out(uint16_t port,uint16_t data);
#ifdef	__cplusplus
}
#endif
#endif
