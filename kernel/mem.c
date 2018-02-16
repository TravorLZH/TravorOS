#include <kernel/mem.h>
#include <errno.h>

#define OFFSET_BLOCK(block) ((block)-9)
#define	SIZE_OFFSET(offset) *((size_t*)offset+4)
#define	NEXT_OFFSET(offset) *((size_t*)offset+8)

unsigned char* mem_ptr; // Dynamic Memory started

void kmem_init(size_t offset){
	mem_ptr=(unsigned char*)offset;
	// TODO: First unallocated memory block
	*mem_ptr=0;	// BYTE: 0: allocated, 1: unallocated
	*((size_t*)mem_ptr+4)=0x1000000; // DWORD: 2GB unallocated
	*((size_t*)mem_ptr+8)=(size_t)mem_ptr;	// Next block's address;
}
void *kmalloc(size_t size){
	char* offset=mem_ptr;
	char* next=offset;
	// If the size of the block is less than requirement or the block is allocated, enter the loop
	while(*offset==1 || SIZE_OFFSET(offset)<size){
		offset=(char*)NEXT_OFFSET(offset);	// goto the next block
	}
	// Set up an allocated block
	*offset=1;					// Identify it's allocated
	SIZE_OFFSET(offset)=size;
	NEXT_OFFSET(offset)=(size_t)offset+size+4;	// next unallocated block's address
	next=(unsigned char*)NEXT_OFFSET(offset);	// Pointer to next
	*next=0;				// Unallocated;
	SIZE_OFFSET(next)=0x1000000-(size_t)next;	// Size of unallocated;
	NEXT_OFFSET(next)=(size_t)next;		// Next unallocated block's address
	return offset+9;
}
void kfree(void* ptr){
	unsigned char* offset=OFFSET_BLOCK(ptr);
	*offset=0;	// Unallocate the memory;
	ptr=NULL;
}

