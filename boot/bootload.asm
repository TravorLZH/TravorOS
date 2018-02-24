; TravorOS: A simple OS running on Intel x86 Architecture
; Copyright (C) 2017  Travor Liu
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <https://www.gnu.org/licenses/>.
;
; bootload.asm: A boot sector that boots a C kernel in 32-bit protected mode
[org	0x7c00]
KERNEL_OFFSET	equ	0x1000	; This is the memory offset to which we will load our kernel

	mov	[BOOT_DRIVE],dl	; BIOS stores our boot drive in DL, so it's
						; best to remember this for later.

	mov	bp,0x9000		; Set-up the stack.
	mov	sp,bp
	mov	bx,MSG_REAL_MODE	; Announce that we are starting
	call	print_string	; booting from 16-bit real mode
	call	load_kernel		; Load our kernel
	mov	bx,MSG_TO_PROT
	call	print_string
	call	switch_to_pm	; Switch to protected mode, from which
							; we will not return

	jmp	$

; Include our useful, hard-earned routines
%INCLUDE	"io.asm"
%INCLUDE	"screen.asm"
%INCLUDE	"disk.asm"
%INCLUDE	"32bit/gdt.asm"
%INCLUDE	"32bit/protectedmode.asm"

[bits	16]

load_kernel:
	mov	bx,MSG_LOAD_KERNEL	; Print a message to say we are loading the kernel
	call	print_string

	mov	bx,KERNEL_OFFSET	; Set-up parameters for our disk_load routine, so
	mov	dh,20				; that we load the first 20 sectors (excluding
	mov	dl,[BOOT_DRIVE]		; the boot sector) from the boot disk (i.e. our
	call	disk_load		; kernel code) to address KERNEL_OFFSET
; This code is inspired by Linux, Torvalds said that if we turned it off now,
; we won't need to worry about it later.
kill_motor:
	mov	dx,0x3F2
	mov	al,0
	out	dx,al
	ret
[bits	32]
; This is where we arrive after switching to and initializing protected mode.
BEGIN_PM:
	call	KERNEL_OFFSET	; Now jump to the address of our loaded
							; kernel code, assume the brace position,
							; and cross your fingers. Here we go!

	jmp	$					; Hang.

; Global variables
BOOT_DRIVE	db	0
MSG_REAL_MODE	db	"[boot]: Started in 16-bit mode",0xD,0xA,0
MSG_TO_PROT		db	"[boot]: Switching from 16-bit to 32-bit...",0xD,0xA,0
MSG_PROT_MODE	db	"SUCCESS",0
MSG_LOAD_KERNEL	db	"[boot]: Loading kernel into memory...",0xD,0xA,0

times	510-($-$$)	db	0
dw	0xAA55
