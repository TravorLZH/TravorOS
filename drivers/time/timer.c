#include <cpu/timer.h>
#include <cpu/isr.h>
#include <kernel/utils.h>
#include <asm/ioports.h>
#include <drivers/screen.h>

size_t tick=0;

void delay(size_t ticks){
	tick=ticks;
	while(tick);
}

static void timer_callback(registers_t regs){
	if(tick>0)tick--;
}

void init_timer(void){
	kprint("Initializing timer...\n");
	register_interrupt_handler(IRQ0,timer_callback);
}
