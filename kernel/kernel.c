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
	kmem_init(0xC0000);
	return 0;
}

