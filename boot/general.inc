KERNEL_LOADED	equ	0x1000
KERNEL_OFFSET	equ	0x100000
STAGE2_OFFSET	equ	0x7E00
KERNEL_SECTORS	equ	48	; This number will always change
CODE_SEGMENT	equ	code_descriptor - gdt_start
DATA_SEGMENT	equ	data_descriptor - gdt_start

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
