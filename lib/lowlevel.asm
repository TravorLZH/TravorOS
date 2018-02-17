[bits	32]
[global set_interrupt]
[global _set_interrupt]
[global clear_interrupt]
[global _clear_interrupt]

_set_interrupt:
set_interrupt:
	push	ebp
	mov	ebp,esp
	sti
	leave
	ret

_clear_interrupt:
clear_interrupt:
	push	ebp
	mov	ebp,esp
	cli
	leave
	ret
