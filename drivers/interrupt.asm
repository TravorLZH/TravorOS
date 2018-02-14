%ifdef MINGW
%define isr_handler _isr_handler
%define irq_handler _irq_handler
%endif
; Defined in isr.c
[extern	isr_handler]
[extern _isr_handler]
[extern	irq_handler]
[extern _irq_handler]

; Common ISR code
_isr_common_stub:
isr_common_stub:
; 1. Save CPU state
	pusha
	mov	ax,ds; Lower 16-bits of eax=ds
	push	eax; Save the data segment descriptord
	mov	ax,0x10; kernel data segment descriptor
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
	add	esp,8; Cleans up the pushed error code and pushed ISR number
	sti
iret; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

; Common IRQ code. Identical to ISR code except for the `call'
; and the `pop ebx'
_irq_common_stub:
irq_common_stub:
; 1. Save CPU state
	pusha
	mov	ax,ds; Lower 16-bits of eax=ds
	push	eax; Save the data segment descriptord
	mov	ax,0x10; kernel data segment descriptor
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	call	irq_handler
	pop	ebx
	mov	ds,bx
	mov	es,bx
	mov	fs,bx
	mov	gs,bx
	popa
	add	esp,8; Cleans up the pushed error code and pushed ISR number
	sti
iret; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

global _isr0
global _isr1
global _isr2
global _isr3
global _isr4
global _isr5
global _isr6
global _isr7
global _isr8
global _isr9
global _isr10
global _isr11
global _isr12
global _isr13
global _isr14
global _isr15
global _isr16
global _isr17
global _isr18
global _isr19
global _isr20
global _isr21
global _isr22
global _isr23
global _isr24
global _isr25
global _isr26
global _isr27
global _isr28
global _isr29
global _isr30
global _isr31
; IRQs
global _irq0
global _irq1
global _irq2
global _irq3
global _irq4
global _irq5
global _irq6
global _irq7
global _irq8
global _irq9
global _irq10
global _irq11
global _irq12
global _irq13
global _irq14
global _irq15

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
; IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Divide By Zero Exception
_isr0:
isr0:

	push byte 0
	push byte 0
	jmp isr_common_stub

; 1: Debug Exception
_isr1:
isr1:
	cli
	push byte 0
	push byte 1
	jmp isr_common_stub

; 2: Non Maskable Interrupt Exception
_isr2:
isr2:
	cli
	push byte 0
	push byte 2
	jmp isr_common_stub

; 3: Int 3 Exception
_isr3:
isr3:
	cli
	push byte 0
	push byte 3
	jmp isr_common_stub

; 4: INTO Exception
_isr4:
isr4:
	cli
	push byte 0
	push byte 4
	jmp isr_common_stub

; 5: Out of Bounds Exception
_isr5:
isr5:
	cli
	push byte 0
	push byte 5
	jmp isr_common_stub

; 6: Invalid Opcode Exception
_isr6:
isr6:
	cli
	push byte 0
	push byte 6
	jmp isr_common_stub

; 7: Coprocessor Not Available Exception
_isr7:
isr7:
	cli
	push byte 0
	push byte 7
	jmp isr_common_stub

; 8: Double Fault Exception (With Error Code!)
_isr8:
isr8:
	cli
	push byte 8
	jmp isr_common_stub

; 9: Coprocessor Segment Overrun Exception
_isr9:
isr9:
	cli
	push byte 0
	push byte 9
	jmp isr_common_stub

; 10: Bad TSS Exception (With Error Code!)
_isr10:
isr10:
	cli
	push byte 10
	jmp isr_common_stub

; 11: Segment Not Present Exception (With Error Code!)
_isr11:
isr11:
	cli
	push byte 11
	jmp isr_common_stub

; 12: Stack Fault Exception (With Error Code!)
_isr12:
isr12:
	cli
	push byte 12
	jmp isr_common_stub

; 13: General Protection Fault Exception (With Error Code!)
_isr13:
isr13:
	cli
	push byte 13
	jmp isr_common_stub

; 14: Page Fault Exception (With Error Code!)
_isr14:
isr14:
	cli
	push byte 14
	jmp isr_common_stub

; 15: Reserved Exception
_isr15:
isr15:
	cli
	push byte 0
	push byte 15
	jmp isr_common_stub

; 16: Floating Point Exception
_isr16:
isr16:
	cli
	push byte 0
	push byte 16
	jmp isr_common_stub

; 17: Alignment Check Exception
_isr17:
isr17:
	cli
	push byte 0
	push byte 17
	jmp isr_common_stub

; 18: Machine Check Exception
_isr18:
isr18:
	cli
	push byte 0
	push byte 18
	jmp isr_common_stub

; 19: Reserved
_isr19:
isr19:
	cli
	push byte 0
	push byte 19
	jmp isr_common_stub

; 20: Reserved
_isr20:
isr20:
	cli
	push byte 0
	push byte 20
	jmp isr_common_stub

; 21: Reserved
_isr21:
isr21:
	cli
	push byte 0
	push byte 21
	jmp isr_common_stub

; 22: Reserved
_isr22:
isr22:
	cli
	push byte 0
	push byte 22
	jmp isr_common_stub

; 23: Reserved
_isr23:
isr23:
	cli
	push byte 0
	push byte 23
	jmp isr_common_stub

; 24: Reserved
_isr24:
isr24:
	cli
	push byte 0
	push byte 24
	jmp isr_common_stub

; 25: Reserved
_isr25:
isr25:
	cli
	push byte 0
	push byte 25
	jmp isr_common_stub

; 26: Reserved
_isr26:
isr26:
	cli
	push byte 0
	push byte 26
	jmp isr_common_stub

; 27: Reserved
_isr27:
isr27:
	cli
	push byte 0
	push byte 27
	jmp isr_common_stub

; 28: Reserved
_isr28:
isr28:
	cli
	push byte 0
	push byte 28
	jmp isr_common_stub

; 29: Reserved
_isr29:
isr29:
	cli
	push byte 0
	push byte 29
	jmp isr_common_stub

; 30: Reserved
_isr30:
isr30:
	cli
	push byte 0
	push byte 30
	jmp isr_common_stub

; 31: Reserved
_isr31:
isr31:
	cli
	push byte 0
	push byte 31
	jmp isr_common_stub

; IRQ handlers
_irq0:
irq0:
	cli
	push byte 0
	push byte 32
	jmp irq_common_stub

_irq1:
irq1:
	cli
	push byte 1
	push byte 33
	jmp irq_common_stub

_irq2:
irq2:
	cli
	push byte 2
	push byte 34
	jmp irq_common_stub

_irq3:
irq3:
	cli
	push byte 3
	push byte 35
	jmp irq_common_stub

_irq4:
irq4:
	cli
	push byte 4
	push byte 36
	jmp irq_common_stub

_irq5:
irq5:
	cli
	push byte 5
	push byte 37
	jmp irq_common_stub

_irq6:
irq6:
	cli
	push byte 6
	push byte 38
	jmp irq_common_stub

_irq7:
irq7:
	cli
	push byte 7
	push byte 39
	jmp irq_common_stub

_irq8:
irq8:
	cli
	push byte 8
	push byte 40
	jmp irq_common_stub

_irq9:
irq9:
	cli
	push byte 9
	push byte 41
	jmp irq_common_stub

_irq10:
irq10:
	cli
	push byte 10
	push byte 42
	jmp irq_common_stub

_irq11:
irq11:
	cli
	push byte 11
	push byte 43
	jmp irq_common_stub

_irq12:
irq12:
	cli
	push byte 12
	push byte 44
	jmp irq_common_stub

_irq13:
irq13:
	cli
	push byte 13
	push byte 45
	jmp irq_common_stub

_irq14:
irq14:
	cli
	push byte 14
	push byte 46
	jmp irq_common_stub

_irq15:
irq15:
	cli
	push byte 15
	push byte 47
	jmp irq_common_stub
