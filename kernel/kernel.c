/*
* TravorOS: A simple OS running on Intel x86 Architecture
* Copyright (C) 2017  Travor Liu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* kernel.c: The core part of the OS kernel (i.e. The heart of the OS) */
#include <config.h>
#include <stdio.h>
#include <drivers/screen.h>
#include <kernel/memory.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <kernel/multiboot.h>
#include <cpu/gdt.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <asm/interrupt.h>
#include <asm/shutdown.h>

int kernel_main(multiboot_info_t *multiboot){
	gdt_install();
	isr_install();
	set_interrupt();
	init_keyboard();
	init_timer(1000);	// Tick per millisecond
	enable_cursor(0x0E,0x0F);
	init_heap(0x200000);
	init_paging();
	char *cmd=(char*)kmalloc(512);
terminal_loop:
	print_at("TravorOS> ",-1,-1,0x0E);
	gets_real(cmd,0xA);
	if(!strcmp(cmd,"help")){
		printf("TravorOS version " VERSION "\n\n");
		printf("Commands:\n");
		printf("about:    Information about this OS\n");
		printf("clear:    Clear the terminal screen\n");
		printf("shutdown: Shutdown the machine\n");
		printf("delay:    Delay 1 second\n");
		printf("reboot:   Reboot this machine\n");
		printf("bsod:     Trigger a Blue Screen of Death\n");
		printf("help:     Display this page\n");
		printf("\nThis OS is built for i386\n");
		printf("Report bugs to " BUGREPORT "\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"about")){
		printf("TravorOS version " VERSION "\nwritten by Travor Liu\nReport bugs to " BUGREPORT "\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"bsod")){
		char *ptr=(char*)0x3000;
		*ptr=1;
		goto terminal_loop;
	}
	if(!strcmp(cmd,"clear")){
		clear_screen(0x07);
		goto terminal_loop;
	}
	if(!strcmp(cmd,"reboot")){
		reboot();
		goto terminal_loop;
	}
	if(!strcmp(cmd,"shutdown")){
		shutdown();
		goto terminal_loop;
	}
	if(!strcmp(cmd,"delay")){
		delay(1000);
		goto terminal_loop;
	}
	if(!strlen(cmd)){
		goto terminal_loop;
	}
	print_at("Unknown Command, type `help' to see available commands\n",-1,-1,0x04);
	goto terminal_loop;
	return 0;
}
