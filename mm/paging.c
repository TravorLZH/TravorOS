#include <kernel/memory.h>
#include <kernel/dbg.h>
#include <drivers/screen.h>
#include <cpu/isr.h>
#include <stdio.h>

extern size_t *frames;
extern size_t nframes;
extern size_t placement_address;
page_directory_t *kernel_directory;
page_directory_t *current_directory;

static void page_fault(registers_t regs){
	size_t faulting_address;
	__asm__ volatile("mov %%cr2,%0" : "=r" (faulting_address));

	int present=!(regs.err_code & 1);	// Page not present
	int rw=regs.err_code & 0x2;	// Write operation
	int us=regs.err_code & 0x4;	// User mode?
	int reserved=regs.err_code & 0x8;	// Overwritten CPU-reserved bits of page entry
	int id=regs.err_code & 0x10;	// Caused by an instruction fetch?

	printf("Page fault! (present: %d, read-only: %d, user-mode: %d, reserved: %d) at 0x%x\n",present,rw,us,reserved,faulting_address);
	PANIC("Page fault");
}

void init_paging(void){
	ktrace("Init paging\n",-1,-1,0xF);
	// The size of physical memory. For the moment we
	// assume it is 16 MB big.
	size_t mem_end_page=0x1000000;
	nframes=mem_end_page / 0x1000;
	frames=(size_t*)kmalloc(INDEX_FROM_BIT(nframes));
	memset(frames,0,INDEX_FROM_BIT(nframes));
	// Let's create a page directory
	ktrace("Allocating page directory\n");
	kernel_directory=(page_directory_t*)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory,0,sizeof(page_directory_t));
	ktrace("Clearing page directory\n");
	current_directory=kernel_directory;
	ktrace("Finish allocating page directory");
	// We need to identity map (phys addr = virt addr) from
	// 0x0 to the end of used memory, so we can access this
	// transparently, as if the paging wasn't enabled.
	// NOTE that we use a while loop here deliberately.
	// inside the loop body we actually change placement_address
	// by calling kmalloc(). A while loop causes this to be
	// computed on-the-fly rather than once at the start;
	size_t i=0;
	while(i<placement_address){
		// Kernel code is readable but not writeable from userspace
		alloc_frame(get_page(i,1,kernel_directory),0,0);
		i+=0x1000;
	}
	ktrace("Registering interrupt handler\n");
	// Before we enable paging, we must register our page fault handler.
	register_interrupt_handler(14,page_fault);
	// Now, enable paging!
	ktrace("Setting CR3\n");
	switch_page_directory(kernel_directory);
}

void switch_page_directory(page_directory_t *dir){
	// FIXME: Triple fault while setting cr3
	current_directory=dir;
	__asm__ volatile("mov %0, %%cr3" :: "r" (dir->tablesPhysical));
	size_t cr0=0;
	__asm__ volatile("mov %%cr0, %0" : "=r" (cr0));
	cr0|=0x80000000;	// Enable paging
	__asm__ volatile("mov %0, %%cr0" :: "r" (cr0));
}

page_t *get_page(size_t address,int make,page_directory_t* dir){
	// Turn address to index
	address/=0x1000;
	// Find the page table containing this address
	size_t table_index=address/1024;
	if(dir->tables[table_index]){	// if this table is already assigned
		return &(dir->tables[table_index]->pages[address%1024]);
	}else if(make){	// If auto create new table
		size_t tmp;
		dir->tables[table_index]=(page_table_t*)kmalloc_ap(sizeof(page_table_t),&tmp);
		memset(dir->tables[table_index],0,0x1000);
		dir->tablesPhysical[table_index]=tmp|0x7;	// Present, rw, user
		return &(dir->tables[table_index]->pages[address%1024]);
	}else{	// Or return an empty one
		return 0;
	}
}
