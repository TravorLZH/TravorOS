#define	NDEBUG
#include <kernel/memory.h>
#include <kernel/dbg.h>
#include <kernel/bsod.h>
#include <bitset32.h>

bitset_t *frame_bitset;
size_t bitset_size=MAX_FRAMES/32;

void set_frame(void *frm)
{
	size_t addr=(size_t)frm;
	bitset_set(frame_bitset,addr/FRAME_SIZE);
}

char is_free_frame(void *frm)
{
	size_t addr=(size_t)frm;
	return bitset_test(frame_bitset,addr/FRAME_SIZE)?0:1;
}

int get_free_frame(void **frame)
{
	int i;
	int ret;
	for(i=0;i<MAX_FRAMES;i++){
		if(ret=is_free_frame((void*)(i*FRAME_SIZE))){
			printvar(ret);
			*frame=(void*)(i*FRAME_SIZE);
			return 0;
		}
	}
	return -ENOMEM;
}

// Allocate frame for a page
void *alloc_frame(page_t *page,char user,char writable)
{
	static size_t times=0;
	times++;
	size_t eip;
	void *free;
	int ret=get_free_frame(&free);	// Find the free frame
	if(ret==-ENOMEM){
		PANIC("Out of Memory!");
	}
	set_frame(free);	// The frame is now ours!
	if(page!=NULL){
		map_frame(page,free,user,writable);
	}
	return free;
}

void free_frame(void *addr)
{
	size_t frm=(size_t)addr;
	bitset_clear(frame_bitset,frm/FRAME_SIZE);
}

void map_frame(page_t *page,void *frame,char user,char writable)
{
	page->present=1;
	page->user=user;
	page->writable=writable;
	page->frame=((size_t)frame)/FRAME_SIZE;
}

