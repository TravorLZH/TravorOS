; syscall.asm: System call handler here
[bits	32]
[extern	print_at]
[extern print_char]
[global	syscall_handler]

; INT 0x80, EAX=5, ESI, String
sys_print:
	push	0x07
	push	-1
	push	-1
	push	esi
	call	print_at
	add	esp,16
	ret

sys_putchar:
	push	0x07
	push	-1
	push	-1
	push	ebx
	call	print_char
	add	esp,16
	ret

syscall_handler:
	push	fin
	cmp	eax,5
	je	sys_print
	cmp	eax,6
	je	sys_putchar
fin:	iret
