/*
* TravorOS: A simple OS running on Intel x86 Architecture
* Copyright (C) 2017  Travor Liu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* memory.h: Memory management stuff for kernel */
#include <def.h>
#ifndef	__MEMORY_H_
#define	__MEMORY_H_
#define	INDEX_FROM_BIT(a)	(a/(8*4))
#define	OFFSET_FROM_BIT(a)	(a%(8*4))

typedef struct page{
	uint8_t present:1;	// Present in memory
	uint8_t rw:1;		// Read-only if clear, read/write if set
	uint8_t user:1;		// Supervisor level only if clear
	uint8_t accessed:1;	// Accessed since last refresh?
	uint8_t dirty:1;	// Written since last refresh
	uint8_t unused:7;	// Amalgamation of unused and reserved bit
	size_t frame:20;	// Frame address (shift to right 12 bits)
}page_t;
typedef struct page_table{
	page_t pages[1024];
} page_table_t;
typedef struct page_directory{
	/* Array of pointers to pagetables */
	page_table_t *tables[1024];
	/* Array of pointers to the pagetables above, but gives their *physical*
	*  location, for loading into CR3 register.
	*/
	size_t tablesPhysical[1024];
	/* The physical address of tablesPhysical. This comes into play when we get
	*  our kernel heap allocated and directory may be in a different location in
	*  virtual memory */
	size_t physicalAddr;
} page_directory_t;
#ifdef	__cplusplus
extern	"C"{
#endif
// Paging Functions
extern void init_paging(void);
/* Change CR3 Value */
extern void switch_page_directory(page_directory_t *dir);
/*
* Get a pointer to the page required.
* If make == 1, if the pagetable in which this page should
* reside isn't created, create it!
*/
extern page_t *get_page(size_t address,int make,page_directory_t *dir);
extern void alloc_frame(page_t *page,int is_kernel,int is_writable);
extern void free_frame(page_t* page);
// Memory Allocator
extern void init_heap(size_t offset);
extern void *kmalloc(size_t size);
extern void *kmalloc_a(size_t size);	// Page aligned
extern void *kmalloc_p(size_t size,size_t* phys);	// Returns physical address
extern void *kmalloc_ap(size_t size,size_t* phys);	// Both
#ifdef	__cplusplus
}
#endif
#endif
