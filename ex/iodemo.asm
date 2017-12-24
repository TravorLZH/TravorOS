[org 0x7c00]

	mov	ah,0x0E		; BIOS interrupt service routine: print character
	mov	al,'A'		; Print char A on the screen
	int	10h			; Call BIOS

	mov	al,0x0F		; Now we are going to move our cursor to the
	mov	dx,0x3D4	; top left of the screen without BIOS.
	out	dx,al		; At first, tell the control I/O port to set
					; the higher byte of the cursor offset
	mov	dx,0x3D5	; Then we send the value to data I/O port
	mov	al,0		; (i.e. zero)
	out	dx,al

	mov	dx,0x3D4	; Now we will tell the control I/O port to
	mov	al,0x0E		; set the lower byte of the cursor offset
	out	dx,al
	mov	al,0		; Set the value to data I/O port
	mov	dx,0x3D5
	out	dx,al
	jmp	$

	times	510-($-$$)	db	0
	dw	0xAA55