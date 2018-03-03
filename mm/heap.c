#include <kernel/memory.h>

size_t placement_address;

void init_heap(size_t base){
	placement_address=base;
}
static void* kmalloc_real(size_t sz,int align,size_t *phys){
	if(align==1 && (placement_address & 0xFFFFF000)){	// If the address is not already page aligned
		// Align it.
		placement_address&=0xFFFFF000;
		placement_address+=0x1000;
	}
	if(phys){
		*phys=placement_address;
	}
	size_t tmp=placement_address;
	placement_address+=sz;
	return (void*)tmp;
}

/* Wrappers for kmalloc_real() */

// Simple one
void* kmalloc(size_t sz){
	return kmalloc_real(sz,0,NULL);
}
// Page aligned
void* kmalloc_a(size_t sz){
	return kmalloc_real(sz,1,NULL);
}
// Returns a physical address
void* kmalloc_p(size_t sz,size_t *phys){
	return kmalloc_real(sz,0,phys);
}
// Page aligned and returns a physical address.
void* kmalloc_ap(size_t sz,size_t *phys){
	return kmalloc_real(sz,phys);
}
