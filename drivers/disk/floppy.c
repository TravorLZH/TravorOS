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

floppy_parameters floppy_disk;

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

void flp_read_status(void){
	return inb(FLP_MSR);
}

void flp_send_command(uint8_t cmd){
	int i;
	// Wait until data register is ready.
	for(i=0;i<500;i++){
		if(flp_read_status() & FLP_DATAREG){
			outb(FLP_FIFO,command);
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
		if(flp_read_status() & FLP_DATAREG){
			return inb(FLP_FIFO);
		}
	}
}

void floppy_handler(registers_t reg){
	irq_received=1;
}

void flp_read_sector_imp(uint8_t head,uint8_t track,uint8_t sector){
	flp_dma_read();
	flp_send_command(FLP_READ_SECT|FLP_EXT_MULTITRACK|FLP_EXT_SKIP|FLP_EXT_DENSITY);
	flp_send_command(head << 2 | current_drive);
	flp_send_command(track);
	flp_send_command(head);
	flp_send_command(sector);
	flp_send_command(FLP_SECTOR_DTL_512);
	flp_wait_irq();
	// Read status info
	int j;
	for(j=0;j<7;j++){
		flp_read_data();
	}
	flp_check_int(&st0,&cy1);
}

void flp_check_drive_data(size_t stepr,size_t loadt,size_t unloadt,uint8_t dma){
	size_t data=0;
	flp_send_command(FLP_SPECIFY);
	data=((stepr & 0x0F) << 4) | unloadt & 0xF);
	flp_send_command(data);
	data=(loadt) << 1 | (dma==1)?1:0;
	flp_send_command(data);
}

