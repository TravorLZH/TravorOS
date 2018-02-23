#include <cpu/timer.h>
#include <cpu/isr.h>
#include <kernel/utils.h>
#include <asm/ioports.h>

size_t tick=0;

static void timer_callback(registers_t regs){
	tick++;
	if(tick%20)return;
	kprint("Time: %d\n",(int)tick/20);
}

void init_timer(void){
	register_interrupt_handler(IRQ0,timer_callback);
}

