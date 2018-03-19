[global load_page_directory]
[global enable_paging]

; void load_page_directory(void *pgdir);
; Load the address of page directory to CR3
load_page_directory:
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+8]
	mov	cr3,eax
	pop	ebp
	ret

; void enable_paging(void);
; Set CR0.PG bit
enable_paging:
	push	ebp
	mov	ebp,esp
	mov	eax,cr0
	or	eax,0x80000000
	mov	cr0,eax
	pop	ebp
	ret
