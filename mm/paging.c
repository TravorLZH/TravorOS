#include <kernel/memory.h>
#include <bitset32.h>
#include <kernel/utils.h>
#include <kernel/bsod.h>
#include <asm/string.h>
#include <drivers/screen.h>
#include <cpu/isr.h>
#include <stdio.h>

extern bitset_t *frame_bitset;
extern size_t bitset_size;
size_t *kernel_directory;
page_t *kernel_table;
page_t *kernel_heap;
page_t *liballoc_heap;

static void page_fault(registers_t regs)
{
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
	bsod_enter("Page Fault",description,&regs);
}

size_t *current_page_directory(void)
{
	register size_t *ret;
	__asm__("movl %%cr3,%0":"=r" (ret)::"eax");
	return ret;
}

void init_paging(void)
{
	assert(sizeof(page_t) == 4);	// Make sure the page union is set up properly
	memset(frame_bitset,0,bitset_size*sizeof(size_t));
	kprint("Initializing Paging...\n");
	frame_bitset=(bitset_t*)kmalloc_a(bitset_size);
	kernel_directory=(size_t*)kmalloc_a(1024*sizeof(size_t));
	kernel_table=(page_t*)kmalloc_a(1024*sizeof(page_t));
	kernel_heap=(page_t*)kmalloc_a(1024*sizeof(page_t));	// Space for placement malloc
	liballoc_heap=(page_t*)kmalloc_a(1024*sizeof(page_t));
	// TODO: Initialize the page directory
	size_t i;
	for(i=0;i<1024;i++){
		/*
		* Set the following flags to the pages:
		* Superwisor: Only kernel-mode can access them
		* Write Enabled: It can be both read from and written to
		* Not present: The page table is not present
		*/
		kernel_directory[i]=0x00000002;
	}
	/* Identity map the first 8MB of the physical memory */
	for(i=0;i<1024;i++){
		map_frame(kernel_table+i,(void*)(i*FRAME_SIZE),0,1);
		set_frame((void*)(i*FRAME_SIZE));
	}
	for(i=0;i<1024;i++){
		map_frame(kernel_heap+i,(void*)((i+1024)*FRAME_SIZE),0,1);
		set_frame((void*)((i+1024)*FRAME_SIZE));
	}
	for(i=0;i<1024;i++){
		liballoc_heap[i].present=0;	// Make sure they are not present
	}
	kernel_directory[0]=((size_t)kernel_table) | 3;		/* 0 - 4MB:  Kernel space */
	kernel_directory[1]=((size_t)kernel_heap) | 3;		/* 4 - 8MB:  Kernel heap */
	kernel_directory[2]=((size_t)liballoc_heap) | 3;	/* 8 - 12MB: liballoc heap */
	register_interrupt_handler(0xE,&page_fault);
	load_page_directory(kernel_directory);
	enable_paging();
	ktrace("SUCCESS");
}

page_t *get_page(void *address,char create,size_t *pgdir)
{
	if(pgdir==NULL){
		pgdir=current_page_directory();
	}
	size_t addr=(size_t)address;
	addr/=PAGE_SIZE;
	size_t tmp;
	size_t table_index=addr/1024;
	if(pgdir[table_index]){
		tmp=pgdir[table_index];
		tmp-=tmp%PAGE_SIZE;
		return (page_t*)(tmp+addr%1024*sizeof(page_t));
	}else if(create){
		ktrace("Page table not found, allocating...");
		tmp=(size_t)kmalloc_a(1024*sizeof(page_t));
		memset((void*)tmp,0,PAGE_SIZE);
		pgdir[table_index]=tmp | 0x7;	// PRESENT, RW, US.
		return (page_t*)tmp+addr%1024;
	}else{
		return NULL;
	}
}

void *alloc_page(void)
{
	void *addr=get_free_page();
	page_t *page=get_page(addr,1,0,current_page_directory());
	page->present=1;
	return addr;
}

void *alloc_pages(int n)
{
	assert(n>0);
	int i,j;
	for(i=0;i<MAX_FRAMES;i++){
}

void free_page(void *address)
{
	size_t addr=(size_t)address;
	addr/=PAGE_SIZE;
	addr*=PAGE_SIZE;	// Make sure it's aligned
	size_t *pgdir=current_page_directory();
	page_t *pg=get_page(address,0,pgdir);
	if(pg){
		free_frame((void*)(pg->frame*FRAME_SIZE));
		pg->present=0;
	}
}

void free_pages(void *address,int n)
{
	assert(n>0);
	size_t *pgdir=current_page_directory();
	size_t addr=(size_t)address;
	int i;
	for(i=0;i<n;i++){
		free_page((void*)addr);
		addr+=PAGE_SIZE;
	}
}

char is_free_page(void *address)
{
	size_t *pgdir=current_page_directory();
	page_t *pg=get_page(address,1,pgdir);
	return pg->present?0:1;
}

void *get_free_page(size_t *pgdir)
{
	if(pgdir==NULL){
		pgdir=current_page_directory();
		ktrace("Using current page directory at address 0x%x",pgdir);
	}
	size_t address;
	page_t *pg=NULL;
	for(address=0;address<MAPPED_SIZE;address+=PAGE_SIZE){
		pg=get_page((void*)address,1,pgdir);
		if(pg->present==0){
			ktrace("Found free page at 0x%x",address);
			return (void*)address;
		}
	}
	return NULL;
}
