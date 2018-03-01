%ifdef	MINGW
%define	enable_paging	_enable_paging
%endif
[global	enable_paging]

PAGING_BASE	equ	0x10000

enable_paging:
	mov	eax,PAGING_BASE
	mov	cr3,eax
