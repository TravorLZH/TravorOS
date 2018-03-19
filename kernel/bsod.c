#include <kernel/bsod.h>
#include <kernel/utils.h>
#include <drivers/screen.h>

// Enter blue screen of death
void bsod_enter(size_t int_no,const char *name,size_t err_code,const char *description,size_t eip){
	clear_screen(0x1F);
	kprint_set_color(0x1F);
	kprintf("An error has occured, and TravorOS has shutdown in order to prevent damage to your computer.\n\n");
	kprintf("The only way to exit this screen is to reboot the machine\n");
	kprintf("\nTechnical Information:\n\n");
	kprintf("0x%x: %s\n\n",int_no,name);
	kprintf("Error Code: 0x%x\n",err_code);
	kprintf("Description:\n%s",description);
	kprintf("\n\nEIP=0x%x\n",eip);
	disable_cursor();
	while(1);
}
