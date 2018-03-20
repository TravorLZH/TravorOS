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
#ifdef	__cplusplus
extern	"C"{
#endif
extern size_t endkernel;
// Global voriables
extern size_t page_directory[1024];
// Paging Functions
extern void init_paging(void);
extern void load_page_directory(void *pgdir);
extern void enable_paging(void);
// Frame function
extern void set_frame(size_t addr);
extern void clear_frame(size_t addr);
extern size_t is_free_frame(size_t addr);
extern int get_free_frame(void);
extern void alloc_frame(size_t *page,char user,char writable);
extern size_t get_frame_no(size_t frame_addr);
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
