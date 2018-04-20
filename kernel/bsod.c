#include <kernel/bsod.h>
#include <kernel/utils.h>
#include <drivers/screen.h>

// Enter blue screen of death
void bsod_enter(const char *name,const char *description,registers_t *regs)
{
	clear_screen(0x1F);
	kprint_set_color(0x1F);
	kprintf("An error has occured, and TravorOS has shutdown in order to prevent damage to your computer.\n\n");
	kprintf("The only way to exit this screen is to reboot the machine\n");
	kprintf("\nTechnical Information:\n\n");
	kprintf("0x%x: %s\n\n",regs->int_no,name);
	kprintf("Error Code: 0x%x\n",regs->err_code);
	kprintf("Description:\n%s",description);
	kprintf("\n\nEAX=0x%x, EBX=0x%x, ECX=0x%x, EDX=0x%x\n"
		"ESI=0x%x, EDI=0x%x, EBP=0x%x, ESP=0x%x",regs->eax,regs->ebx,regs->ecx,regs->edx,regs->esi,regs->edi);
	kprintf("\n\nEIP=0x%x\n",regs->eip);
	disable_cursor();
	while(1);
}
