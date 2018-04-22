; bootload.asm: This is a new bootloader for TravorOS
; It loads second stage at 0x0000:0x07E0 (Directly after this one)
; Also kernel at 0x0000:0x1000
[BITS	16]
[ORG	0x7C00]
jmp	short	bootloader_start

%include "general.inc"

bootloader_start:
	mov	[BOOT_DRIVE],dl
	xor	ax,ax
	mov	ds,ax
	mov	ss,ax
	mov	sp,0x9C00

	mov	si,MSG_BOOT
	call	print_string

	mov	si,MSG_LOAD_STAGE2
	call	print_string

	mov	ah,0	; Reset floppy
	int	13h
	call	load_stage2

	mov	si,MSG_LOAD_KERNEL
	call	print_string
	mov	ah,0
	int	13h
	call	load_kernel
	call	kill_motor	; We don't need floppy now
	jnc	STAGE2_OFFSET
	jmp	$

load_stage2:
	mov	bx,0
	mov	es,bx
	mov	bx,STAGE2_OFFSET
	mov	ah,2	; Read sectors
	mov	al,1	; Read one sector
	mov	ch,0	; First track
	mov	cl,2	; Second sector
	mov	dh,0	; First head
	mov	dl,[BOOT_DRIVE]	; Select current drive
	int	0x13	; Call BIOS
	ret
; Loads kernel at 0x1000
load_kernel:
	xor	ax,ax
	mov	es,ax
	mov	bx,KERNEL_LOADED
	mov	ah,2
	mov	al,KERNEL_SECTORS	; This number will grow soon
	mov	ch,0
	mov	cl,3	; Kernel starts from 3rd sector
	mov	dh,0
	mov	dl,[BOOT_DRIVE]
	int	0x13	; Call BIOS
	ret

; This code is inspired by Linux, Torvalds said that if we turned it off now,
; we won't need to worry about it later.
kill_motor:
	mov	dx,0x3F2
	mov	al,0
	out	dx,al
	ret

; Useful Routines
print_string:
	mov	ah,0xE	; BIOS print character
.looping:
	lodsb	; load character from string stored in SI
	cmp	al,0
	je	.done
	int	0x10
	jmp	.looping
.done:
	ret

MSG_BOOT	db	"[boot]: Hello world!",0xD,0xA,0
MSG_LOAD_STAGE2	db	"[boot]: Loading stage 2 into memory",0xD,0xA,0
MSG_LOAD_KERNEL	db	"[boot]: Loading kernel into memory",0xD,0xA,0
BOOT_DRIVE	db	0

times	510-($-$$)	db	0
dw	0xAA55
