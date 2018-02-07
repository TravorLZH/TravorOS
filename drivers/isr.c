#include <idt.h>
#include <isr.h>
#include <stdio.h>

void isr_install(){
	set_idt_gate(0x10,(uint32_t)int10h);
	set_idt(); // Load with ASM
}

void isr_handler(registers_t r){
	printf("received interrupt: %d\n",r.int_no);
}

