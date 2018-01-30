; Ensures that we jump straight into the kernel's entry function.
[bits	32]
[extern	main]	; Declare that we will be referencing the external symbol 'kernel_main'
[global _cmp]
call	main
jmp	$

; char _cmp(int a,int b): a simple comparison function
; if a is greater than b, returns 1
; if a is less than b, returns -1
; if a is equal to b, returns 0
_cmp:
	push	ebp
	mov	ebp,esp
	push	ebx
	push	ecx
	mov	ebx,[ebp+8]	; Get the first argument
	mov	ecx,[ebp+12]	; Get the second argument
	cmp	ebx,ecx
	jg	.greater
	cmp	ebx,ecx
	je	.equal
	cmp	ebx,ecx
	jl	.less
	jmp	.end
.greater:
	mov	eax,2
	jmp	.end
.equal:
	mov	eax,1
	jmp	.end
.less:
	mov	eax,0
	jmp	.end
.end:	leave
	ret

