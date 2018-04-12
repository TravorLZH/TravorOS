#include <cpu/timer.h>
#include <cpu/isr.h>
#include <kernel/utils.h>
#include <asm/ioports.h>
#include <drivers/screen.h>

size_t tick=0;

void delay(size_t ticks)
{
	tick=ticks;
	while(tick);
}

static void timer_callback(registers_t regs){
	if(tick>0)tick--;
}

void init_timer(size_t frequency)
{
	kprint("Initializing timer with frequency %u Hz...",frequency);
	register_interrupt_handler(IRQ0,timer_callback);
	size_t divisor=1193180 / frequency;
	outb(0x40,divisor & 0xFF);
	outb(0x40,(divisor >> 8) & 0xFF);
	print_at("[OK]\n",-1,-1,0x02);
}
