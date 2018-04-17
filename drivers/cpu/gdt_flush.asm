[global gdt_flush]
KERNEL_CODESEG	equ	0x08

gdt_flush:
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+8]	; Get the GDT pointer's address
	lgdt	[eax]	; Load the new GDT pointer
	mov	ax,0x10	; Offset to data segment
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	mov	ss,ax
	jmp	KERNEL_CODESEG:.flush
.flush:
	leave
	ret
