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
/* isr.h: Declarations of interrupt service routines */
#include <types.h>
#ifndef	__ISR_H_
#define	__ISR_H_
/* Struct which aggregates many registers */
typedef struct {
	uint32_t ds; /* Data segment selector */
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
	uint32_t int_no, err_code; /* Interrupt number and error code (if applicable) */
	uint32_t eip,cs,eflags,useresp,ss; /* Pushed by processor automatically */
} registers_t;

#ifdef	__cplusplus
extern	"C"{
#endif
extern void int50h();
extern void int10h();
extern void isr_handler(registers_t r);
#ifdef	__cplusplus
}
#endif
#endif

