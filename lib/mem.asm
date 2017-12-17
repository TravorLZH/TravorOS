; _api_movbyte(char* dest,char* src)
_api_movbyte:
	push	bp
	mov		bp,sp
	sub		sp,2
	mov		si,[bp+2]
	mov		di,[bp+1]
	mov		[di],[si]
	mov		sp,bp
	pop		bp
	ret