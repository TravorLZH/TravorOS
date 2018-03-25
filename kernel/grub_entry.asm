; Ensures that we jump straight into the kernel's entry function.
[bits	32]
MBOOT_PAGE_ALIGN	equ	1<<0	; Load kernel and modules on a page boundary
MBOOT_MEM_INFO		equ	1<<1	; Provide your kernel with memory info
MBOOT_HEADER_MAGIC	equ	0x1BADB002	; Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.
MBOOT_HEADER_FLAGS	equ	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM	equ	-(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
[global	mboot]
[extern	code]
[extern	bss]
[extern	end]
[global	start]
[extern print_at]
[extern	kernel_main]	; Declare that we will be referencing the external symbol 'kernel_main'
mboot:
dd	MBOOT_HEADER_MAGIC	; GRUB will search for this value on each
						; 4-byte boundary in your kernel file
dd	MBOOT_HEADER_FLAGS	; How GRUB should load your file / settings
dd	MBOOT_CHECKSUM		; To ensure that the above values are correct

dd	mboot
dd	code
dd	bss
dd	end
dd	start

start:
	call	check_a20
	cmp	eax,0
a20_disabled:
	push	0x0F
	push	-1
	push	-1
	push	A20MSG
	call	print_at
	add	esp,16
	call	enable_a20
a20_enabled:
	push	ebx
	cli
	call	kernel_main
	jmp	$

A20MSG	db	"[kernel] Enabling A20",0xA,0

%include "a20.asm"
