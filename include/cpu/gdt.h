/* gdt.h: Global Descriptor Table */
#include <def.h>
#ifndef	__GDT_H_
#define	__GDT_H_
typedef struct gdt_descriptor_struct{
	uint16_t limit;
	void *base;
} __attribute__((packed)) gdt_descriptor_t;
typedef struct gdt_entry_struct{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;	// Access falgs
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;
#ifdef	__cplusplus
extern	"C"{
#endif
extern gdt_entry_t gdt_entries[];
extern gdt_descriptor_t gdt_ptr;
extern void gdt_install(void);
extern void gdt_set_gate(int num,size_t base,size_t limit,uint8_t access,uint8_t gran);
#ifdef	__cplusplus
}
#endif
#endif
