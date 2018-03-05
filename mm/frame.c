#include <kernel/memory.h>
#include <kernel/utils.h>

size_t* frames;
size_t nframes;

// From heap.c
extern size_t placement_address;

// Static function to set a bit in the frame bitset
static void set_frame(size_t frame_addr){
	size_t frame=frame_addr/0x1000;
	size_t index=INDEX_FROM_BIT(frame);
	size_t offset=OFFSET_FROM_BIT(frame);
	frames[index] |= (0x1 << offset);
}
// Clear a bit in the frames bitset
static void clear_frame(size_t frame_addr){
	size_t frame=frame_addr/0x1000;
	size_t index=INDEX_FROM_BIT(frame);
	size_t offset=OFFSET_FROM_BIT(frame);
	frames[index] &= ~(0x1 << offset);
}
// Test if a bit in the frames is set
static size_t test_frame(size_t frame_addr){
	size_t frame=frame_addr/0x1000;
	size_t index=INDEX_FROM_BIT(frame);
	size_t offset=OFFSET_FROM_BIT(frame);
	return (frames[index] & (0x1 << offset));
}
// Find the first free frame
static size_t first_frame(void){
	size_t i,j;
	for(i=0;i<INDEX_FROM_BIT(nframes);i++){
		if(frames[i]!=0xFFFFFFFF){	// Nothing free, exit early
			// at least one bit is free here
			for(j=0;j<32;j++){
				size_t toTest=0x1 << j;
				if(!(frames[i]&toTest)){
					return i*4*8+j;
				}
			}
		}
	}
}
// Allocate a frame
void alloc_frame(page_t *page,int is_kernel,int is_writeable){
	if(page->frame!=0){
		return;	// Frame was already allocated, return straght away
	}else{
		size_t index=first_frame();	// Get the index of first frame
		if(index==(size_t)-1){
			PANIC("NO free frames!");
		}
		set_frame(index*0x1000);	// This frame is now ours
		page->present=1;	// Mark it as present
		page->rw=(is_writeable)?1:0;	// Should it be writeable
		page->user=(is_kernel)?0:1;	// User-mode
		page->frame=index;
	}
}

void free_frame(page_t* page){
	size_t frame;
	if(!(frame=page->frame)){
		return;	// The given page didn't actually have an allocated frame!
	}else{
		clear_frame(frame);	// Frame is now free again
		page->frame=0;	// Page now doesn't have a frame
	}
}
