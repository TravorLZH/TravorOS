os_set_cursor:
	mov	ah,02h
	int	10h
	ret
clear_screen:
	pusha
	mov bh,0
	mov	dl,0
	call	os_set_cursor
	mov	ah,6
	mov	al,0
	mov	bh,7
	mov	cx,0
	mov	dh,24
	mov	dl,79
	int	10h
	popa
	ret