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
/* mem.h: A simple kernel memory allocator */
#include <def.h>
#ifndef	__MEM_H_
#define	__MEM_H_
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
	page_table_t *tables[1024];
	size_t tablesPhysical[1024];
	size_t physicalAddr;
} page_directory_t;
#ifdef	__cplusplus
extern	"C"{
#endif
// Paging Functions
extern void enable_paging(page_directory_t* pd);
extern void disable_paging(void);
// Memory Allocator
extern void heap_init(size_t offset);
extern void *kmalloc(size_t size);
extern void kfree(void* ptr);
#ifdef	__cplusplus
}
#endif
#endif
