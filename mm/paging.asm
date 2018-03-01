[global	enable_paging]

; void enable_paging(size_t base);
enable_paging:
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+8]
	mov	cr3,eax
	mov	eax,cr0
	or	eax,0x80000001	; The PG has no effect if PE is not set
	mov	cr0,eax
	leave
	ret

; void disable_paging(void);
disable_paging:
	push	ebp
	mov	ebp,esp
	mov	eax,cr0
	xor	eax,0x80000000	; Unset PG
	mov	cr0,eax
	leave
	ret
