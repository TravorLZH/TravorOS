#include <config.h>
#include <kernel/utils.h>
#include <string.h>
#include <asm/ioports.h>
#include <cpu/timer.h>
#include <cpu/cpuid.h>
#include <drivers/rtc.h>
#include <liballoc.h>

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
		printf("time:     Get the current time from CMOS\n");
		printf("uname:    Print system information\n");
		printf("hello:    print \"Hello world!\"\n");
		printf("bsod:     Enter blue screen\n");
		printf("delay:    Wait 5 seconds\n");
		printf("shutdown: Shutdown the machine\n");
		printf("clear:    Clear screen\n");
		printf("info:     Print CPU information\n");
		printf("malloc:   Test of kernel memory management\n");
		goto begin;
	}
	if(!strcmp(input_buf,"time")){
		get_time(&time);
		print_time(time);
		goto begin;
	}
	if(!strcmp(input_buf,"uname")){
		printf("TravorOS TRAVOR " VERSION "i386 i386 i386 TravorOS\n");
		goto begin;
	}
	if(!strcmp(input_buf,"hello")){
		printf("Hello world!\n");
		goto begin;
	}
	if(!strcmp(input_buf,"bsod")){
		char *x=(char*)0xA0000000;
		*x=1;
		goto begin;
	}
	if(!strcmp(input_buf,"delay")){
		delay(5000);
		printf("5 seconds passed\n");
		goto begin;
	}
	if(!strcmp(input_buf,"shutdown")){
		outb(0xF4,0x00);	// Shutdown QEMU
		printf("Failed to shutdown\n");
		goto begin;
	}
	if(!strcmp(input_buf,"clear")){
		clear_screen(0x07);
		goto begin;
	}
	if(!strcmp(input_buf,"info")){
		size_t where[4]={0,0,0,0};
		char tmp[5]={0,0,0,0,0};
		printf("Vendor String: ");
		cpuid_string(CPUID_VENDORSTRING,where);
		/*
		* The following code print the vendor string in
		* the correct order:
		* EBX EDX ECX
		*/
		memcpy(tmp,&where[1],4);	// EBX
		printf(tmp);
		memcpy(tmp,&where[3],4);	// EDX
		printf(tmp);
		memcpy(tmp,&where[2],4);	// EBX
		printf(tmp);
		putchar('\n');
		/* Make sure it does not print the value of tmp */
		memset(tmp,0,5);
		/* Print the brand string */
		printf("Brand: ");
		cpuid_string(CPUID_INTELBRANDSTRING,where);
		printf(where);
		cpuid_string(CPUID_INTELBRANDSTRINGMORE,where);
		printf(where);
		cpuid_string(CPUID_INTELBRANDSTRINGEND,where);
		printf(where);
		putchar('\n');
		goto begin;
	}
	if(!strcmp(input_buf,"malloc")){
		char *sth=malloc(10);
		printf("Before freed: 0x%x\n",sth);
		free(sth);
		printf("After freed and malloc'ed: 0x%x\n",sth);
		sth=malloc(10);
		free(sth);
		goto begin;
	}
	kprint_set_color(0x04);
	kprintf("Unknown Command, type `help' for a list of commands\n");
	memset(input_buf,0,BUFSIZ);	// Clear the buffer before re-entering
	goto begin;
}

