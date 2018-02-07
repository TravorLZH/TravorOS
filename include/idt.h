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
/* idt.h: Declarations for Interrupt Descriptor Table */
#include <types.h>
#ifndef	__IDT_H_
#define	__IDT_H_
// Segment selectors
#define	KERNEL_CS	0x08

// Interrupt handler
typedef struct {
	uint16_t low_offset;	/* Lower 16 bits of handler function address */
	uint16_t sel;		/* kernel segment selector */
	uint8_t always0;
	/* First byte
	 * BIt 7: "Interrupt is present"
	 * Bits 6-5: Privilege level of caller (0=kernel..3=user)
	 * Bit 4: Set to 0 for interrupt gates
	 * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
	uint8_t flags;
	uint16_t high_offset; /* higher 16 bits of handler function address */
} __attribute__((packed)) idt_gate_t;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_register_t;

#define	IDT_ENTRIES	256
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;
#ifdef	__cplusplus
extern	"C"{
#endif
extern void set_idt_gate(int n,uint32_t handler);
extern void set_idt();
#ifdef	__cplusplus
}
#endif
#endif
