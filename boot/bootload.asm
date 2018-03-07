; bootload.asm: This will be a new bootloader for TravorOS
; It loads second stage at 0x0000:0x07E0 (Directly after this one)
; Also kernel at 0x0000:0x1000
[BITS	16]
[ORG	0x7C00]
jmp	bootloader_start

MSG_BOOT	db	"[boot]: Hello world!",0xD,0xA,0
MSG_LOAD_STAGE2	db "[boot]: Loading stage 2 into memory",0xD,0xA,0
FAILED_DISK	db	"[error]: Failed to read floppy",0xD,0xA,0
READ_OK	db	"SUCCESS",0xD,0xA,0
BOOT_DRIVE	db	0

%include "general.inc"

bootloader_start:
	mov	[BOOT_DRIVE],dl

	mov	si,MSG_BOOT
	call	print_string

	mov	si,MSG_LOAD_STAGE2
	call	print_string

	mov	ah,0	; Reset floppy
	int	13h

	call	load_stage2
	call	load_kernel
	call	kill_motor	; We don't need floppy now
	jnc	STAGE2_OFFSET
	jmp	$

load_stage2:
	mov	bx,STAGE2_OFFSET	; Load the second stage at offset 0x0000:0x1000
	mov	ah,2	; Read sectors
	mov	al,2	; Read one sector
	mov	ch,0	; First track
	mov	cl,2	; Second sector
	mov	dh,0	; First head
	mov	dl,[BOOT_DRIVE]	; Select current drive
	int	0x13	; Call BIOS
	ret

load_kernel:
	mov	bx,KERNEL_OFFSET
	mov	ah,2
	mov	al,30	; This number will grow soon
	mov	ch,0
	mov	cl,4	; Kernel starts from 4th sector
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

times	510-($-$$)	db	0
dw	0xAA55
