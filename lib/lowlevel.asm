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

[global inb]
[global _inb]
[global outb]
[global _outb]

; char inb(unsigned short port);
_inb:
inb:
	push	ebp
	mov	ebp,esp
	mov	dx,word [ebp+8]
	in	al,dx
	leave
	ret

_outb:
outb:
	push	ebp
	mov	ebp,esp
	mov	dx,word [ebp+8]
	mov	al,byte [ebp+12]
	out	dx,al
	leave
	ret

