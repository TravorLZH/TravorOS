#include <cpu/timer.h>
#include <cpu/isr.h>
#include <kernel/utils.h>
#include <asm/ioports.h>
#include <drivers/screen.h>

size_t tick=0;

static void timer_callback(registers_t regs){
	tick++;
	if(tick%20)return;
	char msg[BUFSIZ];
	sprintf(msg,"Seconds: %d",(int)tick/20);
	print_at(msg,(MAX_COLS-strlen(msg))/2,MAX_ROWS/2,0xF0);
}

void init_timer(void){
	register_interrupt_handler(IRQ0,timer_callback);
}

