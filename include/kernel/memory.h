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
#define	FRAME_SIZE	0x1000
#define	PAGE_SIZE	0x1000
#define	MAPPED_SIZE	0x1000000	// Size of physical memory that is mapped
					// In case it's 16 MB.
#define	MAX_FRAMES	(MAPPED_SIZE/FRAME_SIZE)
#define	MAX_PAGES	MAX_FRAMES	// npages = nframes

#define TABLE_PRESENT(table)	((table) & 0x1)	// Is the page table present?

typedef union page{
	struct{
		char present:1;
		char writable:1;
		char user:1;
		char :2;
		char accessed:1;
		char dirty:1;
		char :2;
		char avail:3;	// Available for this kernel
		size_t frame:20;
	} __attribute__((packed));
	size_t val;
} page_t;
#ifdef	__cplusplus
extern	"C"{
#endif
extern size_t end_kernel;
// Global voriables
extern size_t page_directory[1024];
// Paging Functions
extern void init_paging(void);

extern void load_page_directory(size_t *pgdir);

extern void enable_paging(void);

/* This dude returns the physical address of page directory */
extern size_t *current_page_directory(void);
/************ Page Allocator *****************/
/* Allocate a single page */
extern void *alloc_page(void);

/* Allocate multiple pages */
extern void *alloc_pages(int n);

/* Determine whether a page is free or not */
extern char is_free_page(void *addr);

/* Mark page as present */
extern void set_page(void *addr);

/* Free a single page */
extern void free_page(void *addr);

extern void *get_free_page(size_t *pgdir);

/* Free n pages from addr */
extern void free_pages(void *addr,int n);
/*********************************************/
/************ Page Frame Allocator ***********/
/* Get the first free frame */
extern int get_free_frame(void **frame);

/* Allocate frame for a page */
extern void *alloc_frame(page_t *page,char user,char writable);

/* Determine whether a frame is freed or not */
extern char is_free_frame(void *frameaddr);

/* Free a frame */
extern void free_frame(void *frameaddr);

// This overrides the current frame of the page
extern void map_frame(page_t *page,void *frame,char user,char writable);
/*********************************************/

// Placement Memory Allocator
extern void init_heap(size_t offset);

/* Allocate memory */
extern void *kmalloc(size_t size);

/* Allocate page aligned memory address */
extern void *kmalloc_a(size_t size);

/* Allocate virtual memory and its physical address */
extern void *kmalloc_p(size_t size,size_t* phys);	// Returns physical address

/* Both of the above */
extern void *kmalloc_ap(size_t size,size_t* phys);	// Both
#ifdef	__cplusplus
}
#endif
#endif
