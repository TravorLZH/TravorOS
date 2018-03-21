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
#define	MAPPED_SIZE	0x1000000	// Size of physical memory that is mapped
					// In case it's 16 MB.
#define	MAX_FRAMES	(MAPPED_SIZE/FRAME_SIZE)
// Flags for map_frame
#define	FRAME_WRITABLE	0x01
#define	FRAME_USER	0x02
#define	FRAME_KERNEL	0x00
#define	FRAME_READONLY	0x00
typedef union page{
	struct{
		char present:1;
		char writable:1;
		char user:1;
		char reserved:2;
		char accessed:1;
		char dirty:1;
		char reserved2:2;
		char avail:3;	// Available for this kernel
		size_t frame:20;
	}bits;
	size_t val;
} __attribute__((packed)) page_t;
typedef size_t frame_t;
#ifdef	__cplusplus
extern	"C"{
#endif
extern size_t end_kernel;
// Global voriables
extern size_t page_directory[1024];
// Paging Functions
extern void init_paging(void);
extern void load_page_directory(void *pgdir);
extern void enable_paging(void);
// Frame function
extern frame_t alloc_frame(void);
// This overrides the current frame of the page
extern void map_frame(page_t *page,frame_t frame,char flags);
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
