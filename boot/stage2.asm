; stage2.asm: Switch to protected mode and call C code.
; This program will be loaded at 0x1000
[BITS	16]
[ORG	0x7E00]
jmp	stage2_start

BOOT_DRIVE	db	0
MSG_STAGE2	db	"[stage2]: Hello from stage2 in real mode",0xD,0xA,0
KERNEL_OFFSET	equ	0x1000

gdt_start:

null_descriptor:
	dd	0x0
	dd	0x0
code_descriptor:
	dw	0xFFFF	; Limit
	dw	0x0	; Base
	db	0x0	; Base
	db	10011010b	; (present)1 (privilage)00 (type)1
					; type: (code)1 (conforming)0 (readable)1 (accessed)0
	db	11001111b	; (granularity)1 (32-bit default)1 (64-bit seg)0 (AVL)0
	db	0x0	; Base
data_descriptor:
	; Type flags: (code)0 (expand down)0 (writable)1 (accessed)0
	dw	0xFFFF
	dw	0x0
	db	0x0
	db	10010010b
	db	11001111b
	db	0x0
gdt_end:

gdt_descriptor:
	dw	gdt_end-gdt_start-1
	dd	gdt_start

CODE_SEGMENT	equ	code_descriptor - gdt_start
DATA_SEGMENT	equ	data_descriptor - gdt_start
MSG_PM	db	"[stage2]: Switching to protected mode",0xD,0xA,0

stage2_start:
	; Clear the segment so my code won't go crazy
	mov	ax,0
	mov	ds,ax
	mov	es,ax
	mov	si,MSG_STAGE2
	call	print_string_real

	mov	[BOOT_DRIVE],dl	; Save the current drive number

	call	switch_pm
	jmp	$

switch_pm:
	cli	; Disable interrupt

	mov	si,MSG_PM
	call	print_string_real

	lgdt	[gdt_descriptor]
	mov	eax,cr0	; Set the lowest bit of cr0, so we can
	or	eax,0x1	; switch to protected mode
	mov	cr0,eax

	jmp CODE_SEGMENT:start_pm	; Do a far jump

	jmp	$

print_string_real:
	mov	ah,0xE	; BIOS print character
.looping:
	lodsb	; load character from string stored in SI
	cmp	al,0
	je	.done
	int	0x10
	jmp	.looping
.done:
	ret

[BITS	32]
start_pm:
	mov	ax,DATA_SEGMENT
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	mov	ss,ax

	mov	ebp,0x90000	; Set up stack
	mov	esp,ebp

	mov	esi,HELLO_PM
	call	print_string_pm
	call	KERNEL_OFFSET	; We should not come back from this step
	jmp	$

HELLO_PM	db	"[stage2]: Calling kernel",0
MAX_COLS	equ	80
MAX_ROLS	equ	25
get_cursor_pm:
	push	eax
	push	edx
	mov	ebx,0
	mov	dx,0x3D4
	mov	al,0x0F
	out	dx,al
	mov	dx,0x3D5
	in	al,dx
	mov	bl,al
	mov	dx,0x3D4
	mov	al,0x0E
	out	dx,al
	mov	dx,0x3D5
	in	al,dx
	mov	bh,al
	shl	ebx,1
	pop	edx
	pop	eax
	ret
; EBX: Twice the cursor offset
set_cursor_pm:
	push	eax
	push	edx
	shr	bx,1
	mov	dx,0x3D4
	mov	al,0x0F
	out	dx,al
	mov	dx,0x3D5
	mov	al,bl
	out	dx,al
	mov	dx,0x3D4
	mov	al,0x0E
	out	dx,al
	mov	dx,0x3D5
	mov	al,bh
	out	dx,al
	pop	edx
	pop	eax
	ret
; ESI: String address
print_string_pm:
	pusha
	mov	ebx,0
	mov	edx,0xB8000
	call	get_cursor_pm
	add	edx,ebx
.print_loop:
	lodsb
	mov	ebx,edx
	sub	ebx,0xB8000
	call	set_cursor_pm
	cmp	al,0
	je	.done
	mov	ah,0x0F
	mov	[edx],ax
	add	edx,2
	jmp	.print_loop
.done:
	popa
	ret

times	512-($-$$)	db	0
times	256	dw	0xBABA
