/* init: The core part of the OS kernel (i.e. The heart of the OS) */
#include <stdio.h>
#include <config.h>
#include <drivers/screen.h>
#include <drivers/keyboard.h>
#include <drivers/rtc.h>
#include <drivers/initrd.h>
#include <kernel/memory.h>
#include <kernel/utils.h>
#include <kernel/dbg.h>
#include <kernel/multiboot.h>
#include <kernel/syscall.h>
#include <kernel/fs.h>
#include <cpu/gdt.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <asm/interrupt.h>
#include <asm/ioports.h>

struct tm time;
extern size_t placement_address;	// Placement heap base address
fs_node_t *fs_root=NULL;

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
	uint32_t initrd_location=0;
	uint32_t initrd_end=0;
	gdt_install();
	isr_install();
	set_interrupt();
	init_keyboard();
	init_timer(1000);	// Tick per millisecond
	enable_cursor(0x0E,0x0F);
	init_heap(0x400000);
	if(multiboot!=NULL){
		kprint("Initializing ramdisk\n");
		initrd_location=*((uint32_t*)multiboot->mods_addr);
		initrd_end=*((uint32_t*)(multiboot->mods_addr+4));
		kprint("initrd starts from 0x%x to 0x%x\n",initrd_location,initrd_end);
		placement_address=placement_address>=initrd_end?placement_address:initrd_end;
	}
	init_paging();
	printf("Welcome to TravorOS " VERSION "\n");
	get_time(&time);
	printf("Boot Time: ");
	print_time(time);
	putchar('\n');
	if(multiboot!=NULL){
		kprint("Initializing ramdisk\n");
		init_initrd(initrd_location);
		struct dirent *node=NULL;
		int i;
		while((node=readdir_fs(fs_root,i))!=0){
			fs_node_t *fsnode=finddir_fs(fs_root,node->name);
			if((fsnode->flags&0x07)==FS_DIRECTORY){
				printf("Found directory: %s\n",fsnode->name);
			}else{
				printf("Found file: %s\n",fsnode->name);
				char *buf=(char*)malloc(256);
				uint32_t sz=read_fs(fsnode,0,256,buf);
				int j;
				printf("With content: \"");
				for(j=0;j<sz;j++){
					putchar(buf[j]);
				}
				printf("\"\n");
			}
			i++;
		}
	}
	printf("How did you get here?\n");
	return 0;
}
