#include <kernel/memory.h>

size_t page_directory[1024] __attribute__((aligned(4096)));
size_t first_page_table[1024] __attribute__((aligned(4096)));

void init_paging(void){
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
	// TODO: Initialize the first page table
	for(i=0;i<1024;i++){
		first_page_table[i]=(i*0x1000)|3;	// Attributes: supervisor, rw, present
	}
	page_directory[0]=((size_t)first_page_table) | 3;
	load_page_directory(&page_directory);
}
