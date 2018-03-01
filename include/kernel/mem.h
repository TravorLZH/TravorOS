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
#ifdef	__cplusplus
extern	"C"{
#endif
// Paging Functions
extern void enable_paging(size_t base);
extern void disable_paging(void);
// Memory Allocator
extern void heap_init(size_t offset);
extern void *kmalloc(size_t size);
extern void kfree(void* ptr);
#ifdef	__cplusplus
}
#endif
#endif
