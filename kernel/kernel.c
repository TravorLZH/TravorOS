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
#include <stdio.h>
#include <drivers/floppy.h>
#include <drivers/screen.h>
#include <kernel/mem.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <asm/interrupt.h>

int main(void){
	isr_install();
	set_interrupt();
	init_timer();
	init_keyboard();
	init_floppy();
	kmem_init(0xC0000);
	char cmd[100];
terminal_loop:
	print_at("\nTravorOS> ",-1,-1,0x0E);
	gets(cmd);
	if(!strcmp(cmd,"help")){
		printf("TravorOS v0.5\n\n");
		printf("Available Commands:\n");
		printf("about:  Information about this OS\n");
		printf("clear:  Clear the terminal screen\n");
		printf("reboot: Reboot this machine\n");
		printf("help:   Display this page\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"about")){
		printf("TravorOS written by Travor Liu <travor_lzh@outlook.com>\n");
		goto terminal_loop;
	}
	if(!strcmp(cmd,"clear")){
		clear_screen();
		goto terminal_loop;
	}
	if(!strcmp(cmd,"reboot")){
		uint8_t x=0x02;
		while(x & 0x02){
			x=inb(0x64);
		}
		outb(0x64,0xFE);
		__asm__ ("hlt");
		goto terminal_loop;
	}
	print_at("Unknown Command, type `help' to see available commands\n",-1,-1,0x04);
	goto terminal_loop;
	return 0;
}
