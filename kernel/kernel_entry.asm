; Ensures that we jump straight into the kernel's entry function.
[bits	32]
[extern	main]	; Declare that we will be referencing the external symbol 'kernel_main'
call	main
jmp	$