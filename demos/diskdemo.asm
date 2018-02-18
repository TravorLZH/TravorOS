;org	0x7C00
; Demonstration of disk reading/writing
jmp	bootloader_start

bootloader_start:
	mov	ax,0x7C0
	mov	ds,ax
	mov	es,ax
	mov	ax,0

	mov	ah,0xE
	mov	bx,WRITING_DISK
	call	print_string

	mov	ah,0	; Reset floppy
	int	13h
	
	mov	bx,harddisk_bootloader
	mov	ah,2	; Read sectors
	mov	al,1	; Read one sector
	mov	ch,0	; First track
	mov	cl,2	; Second sector
	mov	dh,0	; First head
	mov	dl,0	; Boot floppy drive
	int	13h

	jc	disk_error
	clc

	mov	bx,harddisk_bootloader	; The offset of loaded hard drive sector
	mov	ah,3	; Write sectors
	mov	al,1	; Write 1 sector
	mov	ch,0	; First track
	mov	cl,1	; First sector
	mov	dh,0	; First head
	mov	dl,0x80	; Write to hard drive
	int	13h
	
	jc	disk_error
	clc
	jmp	$

disk_error:
	mov	bx,DISK_ERROR
	call	print_string
	jmp	$

print_string:
	mov	ah,0Eh
.rep:
	mov	al,[bx]
	add	bx,1
	cmp	al,0
	je	.done
	int	10h
	jmp	.rep
.done:
	ret

WRITING_DISK	db	"Writing to disk...",0xD,0xA,0
DISK_ERROR	db	"Failed on disk operation",0xD,0xA,0

	times	510-($-$$)	db	0
	dw	0xAA55
harddisk_bootloader:
	mov	ax,0x7C0
	mov	ds,ax
	mov	es,ax

	mov	ah,0xE
	mov	al,'A'
	int	10h
	jmp	$

content	db	"Hello world",0xD,0xA,0

	times	510-($-harddisk_bootloader)	db	0
	dw	0xAA55
