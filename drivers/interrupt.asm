; Defined in isr.c
[extern isr_handler]

; Common ISR code
isr_common_stub:
	; 1. Save CPU state
	pusha
	mov	ax,ds	; Lower 16-bits of eax=ds
	push	eax	; Save the data segment descriptord
	mov	ax,0x10	; kernel data segment descriptor
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax

	; 2. Call C handler
	call	isr_handler

	; 3. Restore state
	pop	eax
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	popa
	add	esp,8	; Cleans up the pushed error code and pushed ISR number
	sti
	iret	; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

global	int10h

int10h:
	cli
	push	byte	0
	push	byte	0x10
	jmp	isr_common_stub

