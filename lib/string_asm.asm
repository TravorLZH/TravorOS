[global memcpy1]

; void *memcpy1(void *dest,const void *src,size_t n);
; More efficient memcpy
memcpy1:
	push	ebp
	mov	ebp,esp
	mov	edi,[ebp+8]
	mov	esi,[ebp+12]
	mov	ecx,[ebp+16]
	push	esi
	rep	movsb
	pop	eax
	leave
	ret
