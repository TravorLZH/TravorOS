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
char input_buf[BUFSIZ];
const char host[]="TRAVOR";
const char user[]="kernel";

void print_time(struct tm time){
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

void do_shell(void){
begin:
	kprint_set_color(0x0F);
	kprintf(user);
	kprint_set_color(0x0C);
	kprintf("@");
	kprint_set_color(0x0A);
	kprintf(host);
	kprint_set_color(0x0E);
	kprintf("#");
	putchar(' ');
	kprint_set_color(0x0F);
	gets(input_buf);
	if(!strcmp(input_buf,"help")){
		puts("time:     Get the current time from CMOS\n");
		puts("uname:    Print system information\n");
		puts("hello:    print \"Hello world!\"\n");
		puts("bsod:     Enter blue screen\n");
		puts("delay:    Wait 5 seconds\n");
		puts("shutdown: Shutdown the machine\n");
		puts("clear:    Clear screen\n");
		goto begin;
	}
	if(!strcmp(input_buf,"time")){
		get_time(&time);
		print_time(time);
		goto begin;
	}
	if(!strcmp(input_buf,"uname")){
		puts("TravorOS TRAVOR " VERSION "i386 i386 i386 TravorOS\n");
		goto begin;
	}
	if(!strcmp(input_buf,"hello")){
		puts("Hello world!\n");
		goto begin;
	}
	if(!strcmp(input_buf,"bsod")){
		char *x=(char*)0xA0000000;
		*x=1;
		goto begin;
	}
	if(!strcmp(input_buf,"delay")){
		delay(5000);
		puts("5 seconds passed\n");
		goto begin;
	}
	if(!strcmp(input_buf,"shutdown")){
		outb(0xF4,0x00);	// Shutdown QEMU
		puts("Failed to shutdown\n");
		goto begin;
	}
	if(!strcmp(input_buf,"clear")){
		clear_screen(0x07);
		goto begin;
	}
	kprint_set_color(0x04);
	kprintf("Unknown Command, type `help' for a list of commands\n");
	memset(input_buf,0,BUFSIZ);	// Clear the buffer before re-entering
	goto begin;
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
