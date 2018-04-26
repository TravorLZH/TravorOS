#include <config.h>
#include <kernel/utils.h>
#include <asm/string.h>
#include <asm/ioports.h>
#include <cpu/timer.h>
#include <drivers/rtc.h>

extern struct tm time;
extern void print_time(struct tm);

char input_buf[BUFSIZ];
const char host[]="TRAVOR";
const char user[]="kernel";

void do_shell(void)
{
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
	if(strlen(input_buf)<1){
		goto begin;
	}
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

