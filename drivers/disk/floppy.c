/* floppy.c: A stub for my floppy driver */
#include <stdio.h>
#include <asm/ioports.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <drivers/floppy.h>
#include <cpu/isr.h>
#include <cpu/timer.h>

volatile char irq_received=0;

uint8_t st0=0;
uint8_t cy1=0;
uint8_t current_drive=0;

void flp_init_dma(void){
	outb(0x0A,0x06);	// Mask DMA channel 2
	outb(0xD8,0xFF);	// Reset master flip-flop
	outb(0x04,0x00);	// Address=0x1000
	outb(0x04,0x10);
	outb(0xD8,0xFF);	// Reset master flip-flop
	outb(0x05,0xFF);	// Count to 0x23FF (bytes in 3.5" floppy disk track
	outb(0x80,0x00);	// External page register = 0
	outb(0x0A,0x02);	// Unmask DMA channel 2
}

// Prepare DMA for read
void flp_dma_read(void){
	outb(0x0A,0x06);	// Mask DMA channel 2
	outb(0x0B,0x56);	// Single transfer, address increment,
				// autoinit, read, channel 2
	outb(0x0A,0x02);	// Unmask DMA channel 2
}

// Prepare DMA for write
void flp_dma_write(void){
	outb(0x0A,0x06);
	outb(0x0B,0x5A);	// Single transfer, address increment,
				// autoinit, write, channel 2
	outb(0x0A,0x02);
}

void flp_wait_irq(void){
	while(irq_received==0);
	irq_received=0;
	return;
}

void flp_write_dor(uint8_t val){
	outb(FLP_DOR,val);
}

uint8_t flp_read_status(void){
	return inb(FLP_MSR);
}

void flp_send_command(uint8_t cmd){
	int i;
	// Wait until data register is ready.
	for(i=0;i<500;i++){
		if(flp_read_status() & MSR_DATAREG){
			outb(FLP_FIFO,cmd);
			break;
		}
	}
}

void flp_write_ccr(uint8_t val){
	outb(FLP_CTRL,val);
}

uint8_t flp_read_data(void){
	int i;
	for(i=0;i<500;i++){
		if(flp_read_status() & MSR_DATAREG){
			return inb(FLP_FIFO);
		}
	}
}

void floppy_handler(registers_t reg){
	irq_received=1;
	printf("IRQ fired!\n");
}

int flp_control_motor(char enable){
	size_t motor;
	switch(current_drive){
		case 0:
		motor=DOR_DRIVE0_MOTOR;
		break;
		case 1:
		motor=DOR_DRIVE1_MOTOR;
		break;
		case 2:
		motor=DOR_DRIVE2_MOTOR;
		break;
		case 3:
		motor=DOR_DRIVE3_MOTOR;
		break;
		default:
		return 0;
	}
	if(enable){
		flp_write_dor(current_drive|motor|DOR_RESET|DOR_DMA);
	}else{
		flp_write_dor(DOR_RESET);
	}
	delay(20);
}

void flp_read_sector_imp(uint8_t head,uint8_t track,uint8_t sector){
	size_t st0,cyl;
	flp_dma_read();
	flp_send_command(FLP_READ_SECT|FLP_EXT_MULTITRACK|FLP_EXT_SKIP|FLP_EXT_DENSITY);
	flp_send_command(head << 2 | current_drive);
	flp_send_command(track);
	flp_send_command(head);
	flp_send_command(sector);
	flp_send_command(FLP_SECTOR_DTL_512);
	flp_send_command(
		((sector+1)>=FLP_SECTORS_PER_TRACK)
		?FLP_SECTORS_PER_TRACK:sector+1);
	flp_send_command(GAP3_3_5);
	flp_send_command(0xFF);
	flp_wait_irq();
	// Read status info
	int j;
	for(j=0;j<7;j++){
		flp_read_data();
	}
	flp_check_int(&st0,&cyl);
}

void flp_drive_data(size_t stepr,size_t loadt,size_t unloadt,uint8_t dma){
	size_t data=0;
	flp_send_command(FLP_SPECIFY);
	data=((stepr & 0x0F) << 4) | (unloadt & 0xF);
	flp_send_command(data);
	data=(loadt) << 1 | (dma==1)?1:0;
	flp_send_command(data);
}

int flp_calibrate(uint8_t drive){
	size_t st0,cyl;
	if(drive>=4)return -2;
	flp_control_motor(1);
	int i;
	for(i=0;i<10;i++){
		flp_send_command(FLP_CALIBRATE);
		flp_send_command(drive);
		flp_check_int(&st0,&cyl);
		if(!cyl){
			flp_control_motor(0);
			return 0;
		}
	}
	flp_control_motor(0);
	return -1;
}

void flp_check_int(size_t *st0,size_t *cyl){
	flp_send_command(FLP_CHECK_INT);
	*st0=flp_read_data();
	*cyl=flp_read_data();
}

void flp_lba2chs(size_t lba,size_t *head,size_t *track,size_t *sector){
	*head=(lba%(FLP_SECTORS_PER_TRACK*2))/FLP_SECTORS_PER_TRACK;
	*track=lba/(FLP_SECTORS_PER_TRACK*2);
	*sector=lba%FLP_SECTORS_PER_TRACK+1;
}

int flp_seek(size_t cyl,size_t head){
	size_t st0,cyl0;
	if(current_drive>=4)return -1;
	int i;
	for(i=0;i<10;i++){
		flp_send_command(FLP_SEEK);
		flp_send_command((head)<<2|current_drive);
		flp_send_command(cyl);
		flp_wait_irq();
		if(cyl0==cyl){
			return 0;
		}
	}
	return -1;
}

void flp_disable_controller(void){
	flp_write_dor(0);
}

void flp_enable_controller(void){
	flp_write_dor(DOR_RESET|DOR_DMA);
}

void flp_reset(void){
	size_t st0,cyl;
	flp_disable_controller();
	flp_enable_controller();
	flp_wait_irq();
	int i;
	for(i=0;i<4;i++){
		flp_check_int(&st0,&cyl);
	}
	flp_write_ccr(0);
	flp_drive_data(3,16,240,1);
	flp_calibrate(current_drive);
}

void init_floppy(void){
	register_interrupt_handler(IRQ6,floppy_handler);
	flp_init_dma();
	flp_reset();
	flp_drive_data(13,1,0xF,1);
}

uint8_t *flp_read_sector(size_t sectorLBA){
	if(current_drive>=4){
		return 0;
	}
	int head=0,track=0,sector=1;
	flp_lba2chs(sectorLBA,&head,&track,&sector);
	flp_control_motor(0);
	if(flp_seek(track,head)!=0){
		return 0;
	}
	flp_read_sector_imp(head,track,sector);
	flp_control_motor(1);
	return (uint8_t*)0x1000;
}

