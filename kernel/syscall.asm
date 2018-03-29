; syscall.asm: System call handler here
[bits	32]
[extern	print_at]
[global	syscall_handler]

; INT 0x80, EAX=5, ESI, String
sys_print:
	push	0x0F
	push	-1
	push	-1
	push	esi
	call	print_at
	add	esp,16
	iret

syscall_handler:
	cmp	eax,5
	je	sys_print
	iret
