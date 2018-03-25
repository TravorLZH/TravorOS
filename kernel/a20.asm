check_a20:
	pushad
	mov	edi,0x112345	; Odd megabyte address
	mov	esi,0x012345	; Even
	mov	[esi],esi	; Make sure both addresses contain different values
	mov	[edi],edi	; If A20 is cleared, the two pointers would point to 0x012345 that would contain EDI
	cmpsd	; Compare if equal
	popad
	jne	.a20_on
	mov	eax,0
	ret
.a20_on:
	mov	eax,1
	ret

enable_a20:	; Fast A20
	in	al,0x92
	or	al,2
	out	0x92,al
	ret
