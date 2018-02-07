#include <idt.h>
#include <isr.h>
#include <stdio.h>

void isr_install(){
	set_idt_gate(0x10,(uint32_t)int10h);
	set_idt_gate(0x50,(uint32_t)int50h);
	set_idt(); // Load with ASM
}

void isr_handler(registers_t r){
	printf("received interrupt: %d\n",r.int_no);
	// INT 0x50: Dump register values
	if(r.int_no==0x50){
		printf("EAX: %d (0x%x), ",r.eax,r.eax);
		printf("EBX: %d (0x%x), ",r.ebx,r.ebx);
		printf("ECX: %d (0x%x), ",r.ecx,r.ecx);
		printf("EDX: %d (0x%x), ",r.edx,r.edx);
		printf("EDI: %d (0x%x), ",r.edi,r.edi);
		printf("ESI: %d (0x%x)\n",r.esi,r.esi);
		printf("\nEBP: %d (0x%x)\n",r.ebp,r.ebp);
		printf("ESP: %d (0x%x)\n",r.esp,r.esp);
		printf("EIP: %d (0x%x)\n",r.eip,r.eip);
		printf("CS: %d (0x%x), ",r.cs,r.cs);
		printf("DS: %d (0x%x), ",r.ds,r.ds);
		printf("SS: %d (0x%x)\n",r.ss,r.ss);
	}
}

