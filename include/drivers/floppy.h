#include <def.h>
#ifndef	__FLOPPY_H_
#define	__FLOPPY_H_
// Floppy Disk Controller registers
#define	FLP_DOR	0x3F2
#define	FLP_MSR	0x3F4
#define	FLP_FIFO	0x3F5	// Data register
#define	FLP_CTRL	0x3F7
// FDC DOR Masks
#define	DOR_DRIVE0	0x00
#define	DOR_DRIVE1	0x01
#define	DOR_DRIVE2	0x02
#define	DOR_DRIVE3	0x03
#define	DOR_RESET	0x04
#define	DOR_DRIVE0_MOTOR	0x10
#define	DOR_DRIVE1_MOTOR	0x20
#define	DOR_DRIVE2_MOTOR	0x40
#define	DOR_DRIVE3_MOTOR	0x80
// FDC MSR Masks
#define	MSR_DRIVE0_POS_MODE	0x01
#define	MSR_DRIVE1_POS_MODE	0x02
#define	MSR_DRIVE2_POS_MODE	0x04
#define	MSR_DRIVE3_POS_MODE	0x08
#define	MSR_BUSY	0x10
#define	MSR_DMA		0x20
#define	MSR_DATAIO	0x40
#define	MSR_DATAREG	0x80
// FDC Commands
#define	FLP_READ_TRACK	0x02
#define	FLP_SPECIFY	0x03
#define	FLP_CHECK_STAT	0x04
#define	FLP_WRITE_SECT	0x05
#define	FLP_READ_SECT	0x06
#define	FLP_CALIBRATE	0x07
#define	FLP_CHECK_INT	0x08
#define	FLP_WRITE_DEL_S	0x09
#define	FLP_WRITE_ID_S	0x0A
#define	FLP_READ_DEL_S	0x0C
#define	FLP_FORMAT_TRACK	0x0D
#define	FLP_SEEK	0x0F
// FDC Command Extension
#define	FLP_EXT_SKIP	0x20
#define	FLP_EXT_DENSITY	0x40
#define	FLP_EXT_MULTITRACK	0x80
// FDC Gap length
#define	GAP3_STD	42
#define	GAP3_5_14	32
#define	GAP3_3_5	27
// Size of sector: 2^n * 128
#define	FLP_SECTOR_DTL_128	0
#define	FLP_SECTOR_DTL_256	1
#define	FLP_SECTOR_DTL_512	2
#define	FLP_SECTOR_DTL_1024	4
#ifdef	__cplusplus
extern	"C"{
#endif
// TODO: Implement these functions
extern void init_floppy(void);
extern void flp_wait_irq(void);
extern void flp_write_dor(uint8_t val);
extern uint8_t flp_read_status(void);
#ifdef	__cplusplus
}
#endif
#endif
