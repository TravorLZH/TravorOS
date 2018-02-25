#include <def.h>
#ifndef	__FLOPPY_H_
#define	__FLOPPY_H_
// Base address for the primary and secondary floppydrive controllers
// Drive A is usually on the primary one.
#define	FLP_PRIMARY_BASE			0x03F0
#define	FLP_SECONDARY_BASE			0x0370
// Floppy Disk Controller registers
#define	FLP_STATUS_REG_A			0x0000	/* PS2 Systems */
#define	FLP_STATUA_REG_B			0x0001	/* PS2 Systems */
#define	FLP_DIGITAL_OUTPUT_REG		0x0002
#define	FLP_MAIN_STATUS_REG			0x0004
#define	FLP_DATA_RATE_SELECT_REG	0x0004	/* PS2 Systems */
#define	FLP_DATA_REGISTER			0x0005
#define	FLP_DIGITAL_INPUT_REG		0x0007	/* AT Systems */
#define	FLP_CONFIG_CONTROL_REG		0x0007	/* AT Systems */
#define	FLP_PRIMARY_RESULT_STATUS	0x0000
#define	FLP_SECONDARY_RESULT_STATUS	0x0000
// Flopp Disk Controllery Commands
#define	FLOPPY_FIX_DRIVE_DATA	0x03
#define	FLOPPY_DRIVE_STATUS		0x04
#define	FLOPPY_CALIBRATE_DRIVE	0x07
#define	FLOPPY_INTERRUPT_STATUS	0x08
#define	FLOPPY_READ_SECTOR		0x66
#define	FLOPPY_WRITE_SECTOR		0xC5
#define	FLOPPY_SEEK_TRACK		0x0F
#define	FLOPPY_READ_TRACK		0x42
#define	FLOPPY_FORMAT_TRACK		0x4D
#define	FLOPPY_READ_SECTOR_ID	0x4A
#define	FLOPPY_WRITE_DELETE_SECTOR	0xC5
#define	FLOPPY_READ_DELETE_SECTOR	0xCC

#define	DISK_PARAMETER_ADDRESS	0x00FEFC7	/* Location where disk parameters
											* is store by BIOS */
typedef struct{
	uint8_t steprate_headunload;
	uint8_t headload_ndma;
	uint8_t motor_delay_off;	/* Specified in clock ticks */
	uint8_t bytes_per_sector;
	uint8_t sectors_per_track;
	uint8_t gap_length;
	uint8_t data_length;
	uint8_t format_gap_length;
	uint8_t filler;
	uint8_t head_settle_time;	/* Specified in milliseconds */
	uint8_t motor_start_time;	/* Specified in 1/8 seconds */
} __attribute__((packed)) floppy_parameters;

#ifdef	__cplusplus
extern	"C"{
#endif
// TODO: Implement these functions
extern void init_floppy(void);
extern void flp_wait_irq(void);
extern void flp_write_commmand(int base,char command);
extern void flp_disable_controller(int base);
extern void flp_enable_controller(int base);
extern void flp_reset_controller(int base,char drive);
extern void flp_check_intstatus(int base,uint8_t *st0,uint8_t *cylinder);
extern void flp_configure_drive(int base,char drive);
extern void flp_calibrate_drive(int base,char drive);
extern void flp_wait_data(int base);
extern void flp_motor_on(int base);
extern void flp_motor_off(int base);
extern size_t flp_read_sectors(size_t drive_no,size_t sectors,size_t start,char* addr);
extern size_t flp_write_sectors(size_t drive_no,size_t sectors,size_t start,char* addr);
#ifdef	__cplusplus
}
#endif
#endif
