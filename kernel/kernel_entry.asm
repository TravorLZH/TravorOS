%ifdef MINGW
%define main _main
%define	print_char	_print_char
%endif
; Ensures that we jump straight into the kernel's entry function.
[bits	32]
[extern	main]	; Declare that we will be referencing the external symbol 'kernel_main'
[extern print_char]
push	0x0F
push	-1
push	-1
push	0xA
call	print_char
add	esp,16
call	main
jmp	$
