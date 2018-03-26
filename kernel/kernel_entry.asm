; Ensures that we jump straight into the kernel's entry function.
[bits	32]
jmp start
[extern	kernel_main]	; Declare that we will be referencing the external symbol 'kernel_main'
[extern print_char]
[extern	print_at]
[global start]
start:
	push	0x0F
	push	-1
	push	-1
	push	0xA
	call	print_char
	add	esp,16
	call	check_a20
	cmp	eax,0
a20_disabled:
	push	0x0F
	push	-1
	push	-1
	push	A20MSG
	call	print_at
	add	esp,16
	call	enable_a20
a20_enabled:
	push	0
	call	kernel_main
	jmp	$

A20MSG	db	"[kernel]: Enabling A20",0xA,0

%include "a20.asm"
