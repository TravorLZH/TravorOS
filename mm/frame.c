#include <kernel/memory.h>
#include <kernel/dbg.h>
#include <bitset32.h>

bitset_t frame_bitset[MAX_FRAMES/32];
size_t bitset_size=MAX_FRAMES/32;

void set_frame(frame_t frm){
	bitset_set(frame_bitset,frm);
	assert(bitset_test(frame_bitset,frm));	// Make sure
}

char is_free_frame(frame_t frm){
	return bitset_test(frame_bitset,frm);
}

static get_free_frame(frame_t *frame){
	int i;
	for(i=0;i<MAX_FRAMES;i++){
		if(is_free_frame(i)){
			*frame=i;
		}
	}
	return ENOMEM;
}

// Allocate a new frame
frame_t alloc_frame(void){
	frame_t free;
	int ret=get_free_frame(&free);	// Find the free frame
	if(ret==ENOMEM){
		PANIC("Cannot allocate frame: out of memory");
	}
	set_frame(free);	// The frame is now ours!
	return free;
}

void free_frame(frame_t frm){
	bitset_clear(frame_bitset,frm);
	assert(!bitset_test(frame_bitset,frm));	// Make sure it's freed
}

void map_frame(page_t *page,frame_t frame,char flags){
	char user=flags & FRAME_USER;
	char writable=flags & FRAME_WRITABLE;
	page->bits.present=1;
	page->bits.user=user;
	page->bits.writable=writable;
	page->bits.frame=frame;
}

