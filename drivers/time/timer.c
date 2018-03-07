#include <cpu/timer.h>
#include <cpu/isr.h>
#include <kernel/utils.h>
#include <asm/ioports.h>
#include <drivers/screen.h>

uint8_t lock=0;	// For thread safe
size_t tick=0;

void delay(size_t ticks){
	if(lock){
		kprint("Using by another thread");
	}
	tick=ticks;
	while(tick);
}

static void timer_callback(registers_t regs){
	if(tick>0)tick--;
}

void init_timer(void){
	kprint("Initializing timer...");
	register_interrupt_handler(IRQ0,timer_callback);
	print_at("[OK]\n",-1,-1,0x02);
}
