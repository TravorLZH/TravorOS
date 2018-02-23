#include <def.h>
#ifndef	__FLOPPY_H_
#define	__FLOPPY_H_
#ifdef	__cplusplus
extern	"C"{
#endif
extern void motor_on();
extern void motor_off();
// TODO: Implement these functions
extern size_t read_sectors(size_t drive_no,size_t sectors,size_t start,char* addr);
extern size_t write_sectors(size_t drive_no,size_t sectors,size_t start,char* addr);
#ifdef	__cplusplus
}
#endif
#endif
