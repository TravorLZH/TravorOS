; Reading disk: Load DH sectors to ES:BX from drive DL
disk_load:
	push	dx
	
	mov	ah,0x02
	mov	al,dh
	mov	ch,0x00
	mov	dh,0x00
	mov	cl,0x02
	
	int	0x13
	jc	disk_error
	pop	dx
	cmp	dh,al
	jne	disk_error2
	ret
disk_error:
	mov	bx,DISK_ERROR_MSG
	call	print_string
	call	CRLF
	jmp	$

disk_error2:
	mov	bx,DISK_ERROR_MSG2
	call	print_string
	call	CRLF
	jmp	$
; Variables
DISK_SUCCESS	db	"SUCCESS",0
LOADING_DISK	db	"Loading disk...",0
DISK_ERROR_MSG	db	"ERROR: Failed to read disk",0
DISK_ERROR_MSG2	db	"ERROR: Failed to load disk data",0