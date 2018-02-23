#include <kernel/mem.h>
#include <errno.h>

#define	HEAP_SIZE	0x10000000	// Heap Size: 2GB

typedef struct mem_block memblock_t;

struct mem_block{
	char allocated;
	size_t size;
	memblock_t* prev;
	memblock_t* next;
	char content[];
};

memblock_t* mem_ptr;

static void calculate_free_size(memblock_t* ptr){
	size_t offset=(size_t)mem_ptr;
	size_t szPtr=sizeof(ptr);
	size_t offsetPtr=(size_t)ptr;
	ptr->size=HEAP_SIZE-(offsetPtr-offset);
}

static void calculate_next_address(memblock_t* ptr){
	ptr->next=(memblock_t*)(ptr->content+ptr->size);
}

void kmem_init(size_t offset){
	// TODO: Create the first memory block
	mem_ptr=(memblock_t*)offset;
	mem_ptr->allocated=0;
	mem_ptr->size=HEAP_SIZE;
	mem_ptr->prev=NULL;
	mem_ptr->next=NULL;
}
void *kmalloc(size_t size){
	memblock_t* ptr=mem_ptr;
	do{
		if((ptr->allocated || ptr->size<size) && ptr->next!=NULL){
			ptr=ptr->next;
			continue;
		}
		break;
	}while(1);
	// TODO: Set up an allocated block
	ptr->allocated=1;
	// Create new unallocated block.
	if(ptr->next==NULL){
		ptr->size=size;
		calculate_next_address(ptr);
		ptr->next->allocated=0;
		ptr->next->prev=ptr;
	}
	return ptr->content;
}
void kfree(void* ptr){
	memblock_t* p=(memblock_t*)ptr-16;
	p->allocated=0;
	calculate_free_size(p);
}

