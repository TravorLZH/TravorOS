; A boot sector that boots a C kernel in 32-bit protected mode
[org	0x7c00]
KERNEL_OFFSET	equ	0x1000	; This is the memory offset to which we will load our kernel

	mov	[BOOT_DRIVE],dl	; BIOS stores our boot drive in DL, so it's
						; best to remember this for later.
	
	mov	bp,0x9000		; Set-up the stack.
	mov	sp,bp
	call	clear_screen
	mov	bx,MSG_REAL_MODE	; Announce that we are starting
	call	print_string	; booting from 16-bit real mode
	call	load_kernel		; Load our kernel
	call	switch_to_pm	; Switch to protected mode, from which
							; we will not return
	
	jmp	$

; Include our useful, hard-earned routines
%INCLUDE	"../common/io.asm"
%INCLUDE	"../common/screen.asm"
%INCLUDE	"../common/disk.asm"
%INCLUDE	"../common32/gdt.asm"
%INCLUDE	"../common32/protectedmode.asm"

[bits	16]

load_kernel:
	mov	bx,MSG_LOAD_KERNEL	; Print a message to say we are loading the kernel
	call	print_string
	
	mov	bx,KERNEL_OFFSET	; Set-up parameters for our disk_load routine, so
	mov	dh,15				; that we load the first 15 sectors (excluding
	mov	dl,[BOOT_DRIVE]		; the boot sector) from the boot disk (i.e. our
	call	disk_load		; kernel code) to address KERNEL_OFFSET
	
	ret
[bits	32]
; This is where we arrive after switching to and initializing protected mode.
BEGIN_PM:
;	mov	ebx,MSG_PROT_MODE	; User our 32-bit print routine to
;	call	print_string_pm	; announce we are in protected mode
	
	call	KERNEL_OFFSET	; Now jump to the address of our loaded
							; kernel code, assume the brace position,
							; and cross your fingers. Here we go!
	
	jmp	$					; Hang.
	
; Global variables
BOOT_DRIVE	db	0
MSG_REAL_MODE	db	"Started in 16-bit Real Mode",0xD,0xA,0
MSG_PROT_MODE	db	"Successfully landed in 32-bit Protected Mode",0
MSG_LOAD_KERNEL	db	"Loading kernel into memory",0xD,0xA,0

times	510-($-$$)	db	0
dw	0xAA55