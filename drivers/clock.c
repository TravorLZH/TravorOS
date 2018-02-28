#include <asm/interrupt.h>
#include <kernel/utils.h>
#include <cpu/clock.h>
#include <cpu/isr.h>

static void rtc_handler(registers_t reg){
	outb(0x70,0x0C);	// Select register C
	inb(0x71);			// Just throw away contents;
}

void init_clock(){
	kprint("Initializing RTC...");
	clear_interrupt();
	outb(0x70,0x8B);	// Select register B, and disable NMI
	char prev=inb(0x71);	// Read the current value of register B
	outb(0x70,0x8B);	// Set the index again (a read will reset the index to register D)
	outb(0x71,prev|0x40);// Write the previous value ORed with 0x40, This turns on bit 6 of reg B
	set_interrupt();
	register_interrupt_handler(IRQ8,rtc_handler);
	print_at("[OK]\n",-1,-1,0x02);
}
