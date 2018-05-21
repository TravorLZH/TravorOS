[global load_page_directory]
[global enable_paging]
[global current_page_directory]

; void load_page_directory(size_t *pgdir);
; Load the address of page directory to CR3
load_page_directory:
	push	ebp
	mov	ebp,esp
	mov	eax,[ebp+8]
	mov	cr3,eax
	pop	ebp
	ret

; size_t *current_page_directory(void);
; Get the physical address of the
; current page directory from CR3
current_page_directory:
	push	ebp
	mov	ebp,esp
	mov	eax,cr3
	pop	ebp
	ret

; void enable_paging(void);
; Set CR0.PG bit
enable_paging:
	mov	eax,cr0
	or	eax,0x80000000
	mov	cr0,eax
	ret
