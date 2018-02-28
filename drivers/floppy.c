/* floppy.c: A stub for my floppy driver */
#include <stdio.h>
#include <asm/ioports.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <drivers/floppy.h>
#include <cpu/isr.h>
#include <cpu/timer.h>

volatile char irq_received=0;

char st0=0;
char cylinder=0;

floppy_parameters floppy_disk;

void flp_wait_irq(void){
	while(irq_received==0);
	irq_received=0;
	return;
}

void floppy_handler(registers_t reg){
	irq_received=1;
}

void init_floppy(void){
	kprint("Initializing floppy driver...");
	register_interrupt_handler(IRQ6,floppy_handler);
	memcpy(&floppy_disk,DISK_PARAMETER_ADDRESS,sizeof(floppy_parameters));
	print_at("[OK]\n",-1,-1,0x2);
	flp_reset_controller(FLP_PRIMARY_BASE,0);
}

void flp_check_intstatus(int base,uint8_t *st0,uint8_t *cylinder){
	flp_write_commmand(base,FLOPPY_INTERRUPT_STATUS);
	flp_wait_data(base);
	*st0=inb(base+FLP_DATA_REGISTER);
	flp_wait_data(base);
	*cylinder=inb(base+FLP_DATA_REGISTER);
	ktrace("st0: %u (0x%x), cylinder: %u (0x%x)\n",st0,st0,cylinder,cylinder);
	return;
}

void flp_wait_data(int base){
	// Read main status register of controller and wait until
	// the data is ready in the data register
	while(((inb(base+FLP_MAIN_STATUS_REG))&0xD0)!=0xD0);
	return;
}

void flp_write_commmand(int base,char command){
	outb(base+FLP_DATA_REGISTER,command);
}

void flp_disable_controller(int base){
	outb(base+FLP_DIGITAL_OUTPUT_REG,0x00);
}

void flp_enable_controller(int base){
	outb(base+FLP_DIGITAL_OUTPUT_REG,0x0C);
}

void flp_reset_controller(int base,char drive){
	flp_disable_controller(base);
	flp_enable_controller(base);
	flp_wait_irq();
	flp_check_intstatus(base, &st0, &cylinder);
	outb(base+FLP_CONFIG_CONTROL_REG,0);
	flp_configure_drive(base,drive);
	flp_calibrate_drive(base,drive);
}

void flp_calibrate_drive(int base,char drive){
	flp_motor_on(base);
	flp_write_commmand(base,FLOPPY_CALIBRATE_DRIVE);
	flp_write_commmand(base,drive);
	flp_wait_irq();
	flp_check_intstatus(base,&st0,&cylinder);
}

void flp_motor_on(int base){
	outb(base+FLP_DIGITAL_OUTPUT_REG,0b00011100);
	delay(5);
}
void flp_motor_off(int base){
	outb(base+FLP_DIGITAL_OUTPUT_REG,0);
	delay(5);
}

void flp_configure_drive(int base,char drive){
	flp_write_commmand(base,FLOPPY_FIX_DRIVE_DATA);
	flp_write_commmand(base,floppy_disk.steprate_headunload);
	flp_write_commmand(base,floppy_disk.headload_ndma);
}

void flp_seek_track(uint8_t head,uint8_t cyl,uint8_t drive){
	flp_write_commmand(FLP_PRIMARY_BASE,FLOPPY_SEEK_TRACK);
	flp_write_commmand(FLP_PRIMARY_BASE,((head & 1) << 2) + drive);
	flp_write_commmand(FLP_PRIMARY_BASE,cyl);
	flp_wait_irq();
	flp_check_intstatus(FLP_PRIMARY_BASE,&st0,&cylinder);
}

void flp_read_sector(uint8_t sector,uint8_t head,uint8_t cylinder,uint8_t drive,char* buffer){
	flp_seek_track(head,cylinder,drive);
//	flp_start_dma(0x02,0x44,buffer,511);
	//sleep(floppy_disk.head_settle_time);
}
