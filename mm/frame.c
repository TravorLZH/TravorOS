#define	NDEBUG
#include <kernel/memory.h>
#include <kernel/dbg.h>
#include <kernel/bsod.h>
#include <bitset32.h>

bitset_t *frame_bitset;
size_t bitset_size=MAX_FRAMES/32;

void set_frame(frame_t frm)
{
	bitset_set(frame_bitset,frm);
	assert(bitset_test(frame_bitset,frm));	// Make sure
}

char is_free_frame(frame_t frm)
{
	return bitset_test(frame_bitset,frm)?0:1;
}

int get_free_frame(frame_t *frame)
{
	int i;
	int ret;
	for(i=0;i<MAX_FRAMES;i++){
		if(ret=is_free_frame(i)){
			printvar(ret);
			*frame=i;
			return 0;
		}
	}
	return ENOMEM;
}

// Allocate a new frame
frame_t alloc_page(page_t *page,char user,char writable)
{
	static size_t times=0;
	times++;
	size_t eip;
	frame_t free;
	int ret=get_free_frame(&free);	// Find the free frame
	if(ret==ENOMEM){
		PANIC("Out of Memory!");
	}
	set_frame(free);	// The frame is now ours!
	if(page!=NULL){
		map_frame(page,free,user,writable);
	}
	return free;
}

void free_page(page_t *page)
{
	if(page->frame){
		free_frame((size_t)page->frame);
		page->frame=NULL;
	}
}

void free_frame(frame_t frm)
{
	bitset_clear(frame_bitset,frm);
	assert(!bitset_test(frame_bitset,frm));	// Make sure it's freed
}

void map_frame(page_t *page,frame_t frame,char user,char writable)
{
	page->present=1;
	page->user=user;
	page->writable=writable;
	page->frame=frame;
}

