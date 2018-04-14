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
#include <drivers/screen.h>
#include <drivers/keyboard.h>
#include <kernel/memory.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <kernel/multiboot.h>
#include <kernel/test.h>
#include <cpu/gdt.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <asm/interrupt.h>
#include <asm/shutdown.h>

int kernel_main(multiboot_info_t *multiboot)
{
	gdt_install();
	isr_install();
	set_interrupt();
	init_keyboard();
	//init_timer(1000);	// Tick per millisecond
	enable_cursor(0x0E,0x0F);
	init_heap(0x400000);
	init_paging();
	kbd_test();
	return 0;
}
