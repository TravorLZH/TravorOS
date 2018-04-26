/* init: The core part of the OS kernel (i.e. The heart of the OS) */
#include <stdio.h>
#include <config.h>
#include <drivers/screen.h>
#include <drivers/keyboard.h>
#include <drivers/rtc.h>
#include <kernel/memory.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <kernel/multiboot.h>
#include <kernel/syscall.h>
#include <cpu/gdt.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <asm/interrupt.h>
#include <asm/ioports.h>

struct tm time;

void print_time(struct tm time)
{
	char tmp[3];
	puts("20");
	itoa(time.tm_year,tmp);
	pad_zero(2,tmp);
	puts(tmp);
	putchar('/');
	itoa(time.tm_mon,tmp);
	pad_zero(2,tmp);
	puts(tmp);
	putchar('/');
	itoa(time.tm_mday,tmp);
	pad_zero(2,tmp);
	puts(tmp);
	putchar(' ');
	itoa(time.tm_hour,tmp);
	pad_zero(2,tmp);
	puts(tmp);
	putchar(':');
	itoa(time.tm_min,tmp);
	pad_zero(2,tmp);
	puts(tmp);
	putchar(':');
	itoa(time.tm_sec,tmp);
	pad_zero(2,tmp);
	puts(tmp);
	puts(" GMT\n");
}

int kernel_main(multiboot_info_t *multiboot)
{
	gdt_install();
	isr_install();
	set_interrupt();
	init_keyboard();
	init_timer(1000);	// Tick per millisecond
	enable_cursor(0x0E,0x0F);
	init_heap(0x400000);
	init_paging();
	printf("Welcome to TravorOS " VERSION "\n");
	get_time(&time);
	puts("Boot Time: ");
	print_time(time);
	putchar('\n');
	do_shell();
	return 0;
}
