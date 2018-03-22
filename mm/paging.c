#include <kernel/memory.h>
#include <bitset32.h>
#include <kernel/utils.h>
#include <kernel/bsod.h>
#include <asm/shutdown.h>
#include <drivers/screen.h>
#include <cpu/isr.h>
#include <stdio.h>

extern bitset_t frame_bitset[];
extern size_t bitset_size;
size_t page_directory[1024] __attribute__((aligned(FRAME_SIZE)));
page_t first_page_table[1024] __attribute__((aligned(FRAME_SIZE)));

static void page_fault(registers_t regs){
	size_t faulting_address;
	int present,rw,us,reserved,id;
	present=regs.err_code & 1;	// Page not present
	rw=regs.err_code & 0x2;			// Write protection?
	us=regs.err_code & 0x4;			// User-mode?
	reserved=regs.err_code & 0x8;	// Overwritten CPU-reserved bits of page entry?
	id=regs.err_code & 0x10;		// Caused by an instruction fetch?
	__asm__("movl %%cr2,%0":"=r" (faulting_address));
	char description[512];
	sprintf(description,"Page fault occurs while %s address 0x%x\nPage attributes: %s%s%s%s",
		rw?"writing":"reading",
		faulting_address,
		present?"\0":"not-present ",
		us?"user-mode ":"\0",
		reserved?"cpu-reserved ":"\0",
		id?"instruction-fetch":"\0"
	);
	bsod_enter(regs.int_no,"Page Fault",regs.err_code,description,regs.eip);
}

void init_paging(void){
	assert(sizeof(page_t) == 4);	// Make sure the page union is set up properly
	memset(frame_bitset,0,bitset_size*sizeof(size_t));
	kprint("Initializing Paging...\n");
	// TODO: Initialize the page directory
	size_t i;
	for(i=0;i<1024;i++){
		/* Set the following flags to the pages:
		 * Superwisor: Only kernel-mode can access them
		 * Write Enabled: It can be both read from and written to
		 * Not present: The page table is not present
		*/
		page_directory[i]=0x00000002;
	}
	kprint("Finished filling page directory\n");
	// TODO: Initialize the first page table which maps 4 MB of the physical memory
	for(i=0;i<1024;i++){
		alloc_page(first_page_table+i,FRAME_WRITABLE|FRAME_KERNEL);
	}
	kprint("Finished allocating pages for the first table\n");
	first_page_table[3].val=3*0x1000;	// Create a not-present page
	page_directory[0]=((size_t)first_page_table) | 3;
	register_interrupt_handler(0xE,&page_fault);
	load_page_directory(page_directory);
	enable_paging();
	kprint("Paging Enabled!\n");
}
