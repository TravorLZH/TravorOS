#ifndef	__CMOS_H_
#define	__CMOS_H_
#include <def.h>
#include <asm/ioports.h>
#define	CMOS_STATUS_REG	0x70
#define	CMOS_DATA_REG	0x71
#define	CMOS_WRITE(reg,data)	({ \
	outb(CMOS_STATUS_REG,(reg)|0x80); \
	outb(CMOS_DATA_REG,data); \
})
#define CMOS_READ(reg)	({ \
	outb(CMOS_STATUS_REG,(reg)|0x80); \
	inb(CMOS_DATA_REG); \
})
#endif
