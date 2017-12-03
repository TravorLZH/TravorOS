os_sleepsec:
	pusha
	mov	ah,86h
	mov	cx,0Fh
	mov	dx,4240h
	int	15h
	popa
	ret
os_set_cursor:
	mov	ah,02h
	int	10h
	ret
os_print_string:
	mov	ah,0Eh
.repeat:
	lodsb
	cmp	al,0
	je	.done
	int	10h
	jmp	.repeat
.done:
	ret
os_read_char:
	mov	ah,00h
	int	16h
	ret
os_clear_screen:
	pusha
	pusha
	mov bh,0
	mov	dl,0
	call	os_set_cursor
	popa
	mov	al,0
	mov	bh,7
	mov	cx,0
	mov	dh,24
	mov	dl,79
	int	10h
	popa
	ret